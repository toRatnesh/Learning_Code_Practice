/*****

References
    Anthony Williams - C++ Concurrency in Action

9 Advanced thread management

    We’ll look at mechanisms for managing threads and tasks, starting with the automatic 
    management of the number of threads and the division of tasks between them

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

9.1.2 Waiting for tasks submitted to a thread pool

    With thread pools, you’d need to wait for the tasks submitted to the
    thread pool to complete, rather than the worker threads themselves

    You can have the submit() function return a task handle of some description that you can then
    use to wait for the task to complete.

    Because std::packaged_task<> instances are not copyable, just movable,  you can no longer use std::function<> 
    for the queue entries, Instead, you must use a custom function wrapper that can handle move-only types. 
    
    This is a simple type-erasure class with a function call operator. You only need to handle functions 
    that take no parameters and return void, so this is a straightforward virtual call in the implementation.

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
    thsafe_queue<function_wrapper> m_queue;
    std::vector<std::jthread> m_threads;

    void worker_thread() {
        while (not m_done) {
            function_wrapper task;
            if (m_queue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
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
        //std::packaged_task task(std::move(callable));		// CTAD
        //std::future res(task.get_future());			// CTAD
        m_queue.push(std::move(task));
        return res;
    }
};

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

    const int num_elems = 11;
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
This pool allows you to wait for your tasks and have them return results.

The thread pool takes care of the exception safety too. Any exception thrown by
the task gets propagated through the future returned from submit(), and if the
function exits with an exception, the thread pool destructor abandons any
not-yet-completed tasks and  waits for the pool threads to finish.

But it’s not so good for situations where the tasks depend on other tasks also
submitted to the thread pool.
**********/

/*****
    END OF FILE
**********/

