/*****

References
    Anthony Williams - C++ Concurrency in Action

9 Advanced thread management

	We’ll look at mechanisms for managing threads and tasks, starting with the automatic management 
	of the number of threads and the division of tasks between them.


9.1 Thread pools

	On most systems, it’s impractical to have a separate thread for every task that, can potentially be done 
	in parallel with other tasks, but you’d still like to take advantage of the available concurrency where possible.

	A thread pool allows you to accomplish this; tasks that can be executed concurrently are submitted to the pool, 
	which puts them on a queue of pending work. 
	Each task is then taken from the queue by one of the worker threads, which executes the task before 
	looping back to take another from the queue.

	design issues when building a thread pool, such as
		how many threads to use,
		the most efficient way to allocate tasks to threads, and
		whether or not you can wait for a task to complete

9.1.3 Tasks that wait for other tasks

	To process outstanding thread while you are waiting for other threads to complete.

	The simplest way to do this is to add a new function on thread_pool to run a task from the queue 
	and manage the loop yourself, so we’ll go with that.

	Advanced thread pool implementations might add logic into the wait function 
	or additional wait functions to handle this case, possibly prioritizing the task being waited for.


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
#include <list>

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
	    m_queue.push(std::move(task));
	    return res;
	}


    void run_pending_task()
    {
	function_wrapper task;
	if(m_queue.try_pop(task))
	{
	    task();
	}
	else
	{
	    std::this_thread::yield();
	}
    }	
};

template<typename T>
struct sorter
{
    thread_pool pool;

    std::list<T> do_sort(std::list<T>& chunk_data)
    {
	if(chunk_data.empty())
	{
	    return chunk_data;
	}

	std::list<T> result;
	result.splice(result.begin(), chunk_data, chunk_data.begin());

	T const& partition_val = *result.begin();

	typename std::list<T>::iterator divide_point = 
	    std::partition(chunk_data.begin(), chunk_data.end(), [&](T const& val){return val < partition_val;});

	std::list<T> new_lower_chunk;
	new_lower_chunk.splice(new_lower_chunk.end(), chunk_data, chunk_data.begin(), divide_point);

	std::future<std::list<T> > new_lower = 
	    pool.submit(std::bind(&sorter::do_sort, this, std::move(new_lower_chunk)));

	std::list<T> new_higher(do_sort(chunk_data));

	result.splice(result.end(), new_higher);

	while(new_lower.wait_for(std::chrono::seconds(0)) == std::future_status::timeout)
	{
	    pool.run_pending_task();
	}

	result.splice(result.begin(), new_lower.get());

	return result;
    }
};


template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
	return input;
    }

    sorter<T> s;
    return s.do_sort(input);
}

template<typename T>
void display_list(std::list<T> input) {
    for(const auto & elem : input) { 
	std::cout << elem << ' '; 
    }
    std::cout << '\n';
}

int main() {

    std::list<int> list_int{2, 3, 9, 4, 6, 8, 2, 19, 18, 20, 56, 75, 8, 19, 2, 4, 6, 33, 21};
    std::cout << "Unsorted list:\n";
    display_list(list_int);

    auto res = parallel_quick_sort(list_int);
    std::cout << "Sorted list:\n";
    display_list(res);

    return 0;
}


// This pool allows tasks to wait for other tasks.


/*****
    END OF FILE
**********/

