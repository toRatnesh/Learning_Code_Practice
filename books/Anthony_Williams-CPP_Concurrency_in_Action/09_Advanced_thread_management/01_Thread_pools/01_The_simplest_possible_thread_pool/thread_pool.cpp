/*****

References
    Anthony Williams - C++ Concurrency in Action

9 Advanced thread management

We’ll look at mechanisms for managing threads and tasks, starting with 
the automatic management of the number of threads and the division of tasks between them.


9.1 Thread pools

On most systems, it’s impractical to have a separate thread for every task that, can potentially be done in parallel with other tasks, 
but you’d still like to take advantage of the available concurrency where possible.

A thread pool allows you to accomplish this; tasks that can be executed concurrently are submitted to the pool, 
which puts them on a queue of pending work. Each task is then taken from the queue by one of the worker threads, 
which executes the task before looping back to take another from the queue.

design issues when building a thread pool, such as 
	how many threads to use,
	the most efficient way to allocate tasks to threads, and 
	whether or not you can wait for a task to complete

9.1.1 The simplest possible thread pool
A simplest thread pool is
    a fixed number (typically std::thread::hardware_concurrency()) of worker threads  that process work
    When you have work to do, you call a function to put it on the queue of pending work
    Each worker thread takes work off the queue, runs the specified task, and then goes back to the queue for more work
    
    there’s no way to wait for the task to complete
    If you need to do this, you have to manage the synchronization yourself

For many purposes this simple thread pool will suffice, especially if the tasks are entirely independent 
and don’t return any values or perform any blocking operations.
But there are also many circumstances where this simple thread pool may not adequately address your needs, 
and yet others where it can cause problems such as deadlock. 

Also, in simple cases you may be better served using std::async

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


class thread_pool {
    std::atomic_bool							    m_done;
	thsafe_queue<std::function<void()>>             m_queue;
	std::vector<std::jthread>					    m_threads;
	
	void worker_thread() {
		while(not m_done) {
			std::function<void()>	task;
			if(m_queue.try_pop(task)) {
				task();
			}
			else {
				std::this_thread::yield();
			}
		}
	}
	
    public:
	
	~thread_pool() {
		m_done = true;
	}
	
	thread_pool() : m_done(false) {
		const unsigned thread_count = std::thread::hardware_concurrency();
		try {
			for(unsigned i = 0; i < thread_count; ++i) {
				//m_threads.push_back(
				//	std::jthread(&thread_pool::worker_thread, this)
				//);
				m_threads.emplace_back(&thread_pool::worker_thread, this);
			}	
		} catch(...) {
			m_done = true;
			throw;
		}
	}
	
	template<typename Func_t>
	void submit(Func_t callable) {
		m_queue.push(std::function<void()>(callable));
	}
	
};

std::osyncstream sync_cout(std::cout);

void routine_01() {
    sync_cout << "Inside routine " << __func__ << " , thread id " << std::this_thread::get_id() << '\n';
}

void routine_02() {
    sync_cout << "Inside routine " << __func__ << " , thread id " << std::this_thread::get_id() << '\n';
}

void routine_03() {
    sync_cout << "Inside routine " << __func__ << " , thread id " << std::this_thread::get_id() << '\n';
}

int main() {

    thread_pool tpool;
    tpool.submit(routine_01);
    tpool.submit(routine_02);
    tpool.submit(routine_03);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}

/*****
    END OF FILE
**********/

