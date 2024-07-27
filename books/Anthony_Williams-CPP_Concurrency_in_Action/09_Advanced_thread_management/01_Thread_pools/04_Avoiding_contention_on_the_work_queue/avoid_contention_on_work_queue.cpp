/*****

References
    Anthony Williams - C++ Concurrency in Action

9 Advanced thread management

We’ll look at mechanisms for managing threads and tasks, starting with
the automatic management of the number of threads and the division of tasks
between them.


9.1 Thread pools

On most systems, it’s impractical to have a separate thread for every task that,
can potentially be done in parallel with other tasks, but you’d still like to
take advantage of the available concurrency where possible.

A thread pool allows you to accomplish this; tasks that can be executed
concurrently are submitted to the pool, which puts them on a queue of pending
work. Each task is then taken from the queue by one of the worker threads, which
executes the task before looping back to take another from the queue.

design issues when building a thread pool, such as
        how many threads to use,
        the most efficient way to allocate tasks to threads, and
        whether or not you can wait for a task to complete

9.1.4 Avoiding contention on the work queue

As the number of processors increases, there’s increasing contention on the queue.
This can be a real performance drain; even if you use a lock-free queue so there’s no explicit waiting, 
cache ping-pong can be a substantial time sink.

One way to avoid cache ping-pong is to use a separate work queue per thread.
Each thread then posts new items to its own queue and takes work from the global work queue only if there’s no work on its own individual queue.

**********/

#include <condition_variable>
#include <exception>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <string>
#include <syncstream>
#include <thread>
#include <vector>

#include "thsafe_queue.hpp"

class function_wrapper {
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };
    std::unique_ptr<impl_base> impl;
    template <typename F>
    struct impl_type : impl_base {
        F f;
        impl_type(F&& f_) : f(std::move(f_)) {}
        void call() { f(); }
    };

   public:
    function_wrapper() = default;
    function_wrapper(function_wrapper&& other) : impl(std::move(other.impl)) {}
    function_wrapper& operator=(function_wrapper&& other) {
        impl = std::move(other.impl);
        return *this;
    }

    function_wrapper(const function_wrapper&) = delete;
    function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator=(const function_wrapper&) = delete;

    template <typename F>
    function_wrapper(F&& f) : impl(new impl_type<F>(std::move(f))) {}

    void operator()() { impl->call(); }
};

class thread_pool {
    std::atomic_bool m_done;
    thsafe_queue<function_wrapper> m_pool_queue;
    std::vector<std::jthread> m_threads;

    using local_queue_t = std::queue<function_wrapper>;
    static thread_local std::unique_ptr<local_queue_t> m_local_queue;


    void run_pending_task() {
        function_wrapper task;
        if(m_local_queue && (not m_local_queue->empty())) {
            task = std::move(m_local_queue->front());
            m_local_queue->pop();
            task();
        } else if (m_pool_queue.try_pop(task)) {
            task();
        } else {
            std::this_thread::yield();
        }
    }

    void worker_thread() {
        m_local_queue.reset(new local_queue_t);
        while (not m_done) {
            run_pending_task();
        }
    }

   public:
    ~thread_pool() { m_done = true; }

    thread_pool() : m_done(false) {
        const unsigned thread_count = std::thread::hardware_concurrency();
        try {
            for (unsigned i = 0; i < thread_count; ++i) {
                m_threads.push_back(
                    std::jthread(&thread_pool::worker_thread, this));
            }
        } catch (...) {
            m_done = true;
            throw;
        }
    }

    template <typename Func>
    //std::future<std::result_of_t<Func()>> submit(Func callable) 
    std::future<std::invoke_result_t<Func>> submit(Func callable) 
    {
        //typedef std::result_of_t<Func()> res_t;
        using res_t = std::invoke_result_t<Func>;
        std::packaged_task<res_t()> task(std::move(callable));
        std::future<res_t> res(task.get_future());
        if(m_local_queue) {
            m_local_queue->push(std::move(task));
        } else {
            m_pool_queue.push(std::move(task));
        }
        return res;
    }
};

thread_local std::unique_ptr<thread_pool::local_queue_t> thread_pool::m_local_queue;

std::osyncstream sync_cout(std::cout);

template <typename Iterator, typename T>
struct accumulate_block {
    T operator()(Iterator first, Iterator last) {
        return std::accumulate(first, last, T());
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (!length) {
        return init;
    }
    unsigned long const block_size = 25;
    unsigned long const num_blocks = (length + block_size - 1) / block_size;
    std::vector<std::future<T>> futures(num_blocks - 1);
    thread_pool pool;
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        futures[i] = pool.submit(
            [=] { return accumulate_block<Iterator, T>()(block_start, block_end); }
            );
        block_start = block_end;
    }
    T last_result = accumulate_block<Iterator, T>()(block_start, last);
    
    T result = init;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        result += futures[i].get();
    }
    result += last_result;

    return result;
}

int main() {

    const int num_elems = 9999;
    std::vector<int> vec_ints(num_elems);
    
    
    for(int i = 0; i < num_elems; ++i) {
        vec_ints.emplace_back(i);
    }

    auto res = parallel_accumulate(vec_ints.cbegin(), vec_ints.cend(), 0);
    std::cout << "Result is " <<  res << '\n';

    //std::this_thread::sleep_for(std::chrono::seconds(5));    

    return 0;
}

/*****

You’ve used a std::unique_ptr<> to hold the thread-local work queue because you don’t want other threads that aren't part of your thread pool to have one
submit() checks to see if the current thread has a work queue. If it does, it’s a pool thread, and you can put the task on the local queue; otherwise, you need to put the task on the pool queue as before.
run_pending_task(), check to see if there are any items on the local queue. If there are, you can take the front one and process it; notice that the local queue can be a plain std::queue<> because it’s only ever accessed by the one thread. If there are no tasks on the local queue, you try the pool queue as before.

Drawback:
This works fine for reducing contention, but when the distribution of work is uneven, it can easily result in one thread having a lot of work in its queue while the others have no work do to.
Thankfully, there is a solution to this: allow the threads to steal work from each other’s queues if there’s no work in their queue and no work in the global queue.

**********/

/*****
    END OF FILE
**********/

