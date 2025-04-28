/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/thread/thread
	https://en.cppreference.com/w/cpp/thread/async

Item 36: Specify std::launch::async if asynchronicity is essential

auto fut1 =	std::async(f);

There are two std::async launch policy
	1.	std::launch::async		
			f must be run asynchronously, i.e., on a different thread
	2.	std::launch::deferred	
			f’s execution is deferred until get or wait is called on the future returned by std::async
			When get or wait is invoked, f will execute synchronously
			If neither get nor wait is called, f will never run

Default policy
	std::async’s default launch policy is these or-ed together
	The default policy thus permits f to be run either asynchronously or synchronously.

	auto fut1 =	std::async(f);	// f using default launch policy
	auto fut2 =	std::async(std::launch::async | std::launch::deferred, f);


	with the default launch policy, given a thread t executing this statement,
	auto fut = std::async(f);
		• It’s not possible to predict whether f will run concurrently with t
		• It’s not possible to predict whether f runs on a thread different from the thread invoking get or wait on fut.
		• It may not be possible to predict whether f runs at all,


	The default launch policy’s scheduling flexibility often mixes poorly with the use of thread_local variables
	
	It Also affects wait-based loops using timeouts, because calling wait_for or wait_until on a task (see Item 35) 
	that’s deferred yields the value std::launch::deferred.
	
using std::async with the default launch policy for a task is fine as long as the following conditions are fulfilled:
	•	The task need not run concurrently with the thread calling get or wait.
	•	It doesn’t matter which thread’s thread_local variables are read or written.
	•	Either there’s a guarantee that get or wait will be called on the future returned by std::async 
		or it’s acceptable that the task may never execute.
	•	Code using wait_for or wait_until takes the possibility of deferred status into account.	
		
std::launch::async policy
	to guarantee that std::async will schedule the task for truly asynchronous execution
	
	You may write a wrapper to call always with a std::launch::async policy like this
	template<typename F, typename... Ts>
	inline
	// std::future<typename std::result_of<F(Ts...)>::type>	// C++11
	auto // C++14
	reallyAsync(F&& f, Ts&&... params)
	{
		return std::async(std::launch::async,
							std::forward<F>(f),
							std::forward<Ts>(params)...);
	}

Summary
    •	The default launch policy for std::async permits both asynchronous and synchronous task execution.
    •	This flexibility leads to uncertainty when accessing thread_locals, 
        implies that the task may never execute, and affects program logic for timeout-based wait calls.
    •	Specify std::launch::async if asynchronous task execution is essential.

**********/

#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <vector>

void doAsyncWork(const std::string str) {
    std::cout << "Inside " << __func__ 
    << ", thread id " << std::this_thread::get_id() 
    << ", " << str << '\n';
}

void sleepInFunc(const std::string str) {
    std::cout << "Inside " << __func__ 
    << ", thread id " << std::this_thread::get_id() 
    << ", " << str << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main() {
    constexpr size_t    LOOP_SIZE = 5;
    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';

    std::vector<std::future<void>>  fut_vec;
    std::vector<std::future<void>>  l_def_fut;

    for(size_t i = 0; i < LOOP_SIZE; ++i) {
        l_def_fut.push_back(std::async(std::launch::deferred, doAsyncWork, "using async with std::launch::deferred policy"));
    }

    for(size_t i = 0; i < LOOP_SIZE; ++i) {
        fut_vec.push_back(std::async(std::launch::async, doAsyncWork, "using async with std::launch::async policy"));
    }

    for(size_t i = 0; i < LOOP_SIZE; ++i) {
        fut_vec.push_back(std::async(doAsyncWork, "using async with default policy"));
    }


    auto l_fut_w = std::async(sleepInFunc, "using async with default policy - will wait for its completion in wrong way");

    while(l_fut_w.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready) {
        std::cout << "Wrongly waiting for a task with future\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    auto l_fut_c = std::async(sleepInFunc, "using async with default policy - will wait for its completion in correct way");

    if(l_fut_c.wait_for(std::chrono::seconds(0)) == std::future_status::deferred) {
        l_fut_c.get();
    } else {
        while(l_fut_c.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready) {
            std::cout << "Correctly waiting for a task with future\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::cout << "\nCalling get on deferred future object, without this there is not guarantee that it will run\n";
    for(auto & l_temp_fut : l_def_fut) {
    	l_temp_fut.get();
    }

    return 0;
}

/*****
    END OF FILE
**********/

