/*****

References
    Anthony Williams - C++ Concurrency in Action

4.2 Waiting for one-off events with futures

	C++ Standard Library models one-off event with a future
	The waiting thread somehow obtains a future representing that event
	The thread can then wait on the future to see if the event has occurred.
	A future may have data associated with it, or it may not.
	Once an event has happened (and the future has become ready), the future can’t be reset.
	
C++ Standard Library provides two forms of futures
	std::future<>
		unique futures
		one and only instance that refers to its associated event

	std::shared_future<>
		shared futures
		multiple instances of std::shared_future may refer to the same event
		all the instances will become ready at the same time, and they may all access any data associated with the event
		multiple threads may each access their own copy of std::shared_future<> without further synchronization
		
	Associated data is the reason these are templates
	The std:future<void> and std::shared_future<void> template specializations should be used where there’s no associated data.
	
	future objects themselves don’t provide synchronized accesses

	To to associate a std::future with a task, we can use
	-> std::async
	-> std::packaged_task<>
	-> std::promise<>	

For more info visit:

	https://en.cppreference.com/w/cpp/thread/future
	https://en.cppreference.com/w/cpp/thread/shared_future
	https://en.cppreference.com/w/cpp/thread/async
	https://en.cppreference.com/w/cpp/thread/packaged_task
	https://en.cppreference.com/w/cpp/thread/promise

4.2.1 Returning values from background tasks

	use std::async to start an asynchronous task for which you don’t need the result right away
	std::async returns a std::future object, which will eventually hold the return value of the function
	to get value, call get() on the future, and the thread blocks until the future is ready and then returns the value
	
	std::async makes it easy to divide algorithms into tasks that can be run concurrently

**********/

#include <iostream>
#include <future>
#include <string>
#include <thread>
#include <chrono>

int get_ascii_sum(std::string str) {
    int res = 0;
    int i   = 0;
    std::cout << "Executing some time taking operation\n";
    for(auto & elem : str) {
        res += elem;

        ++i;
        std::cout << "Executing some time taking operation " << std::string(i, '.') << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return res;
}

int main() {
    std::cout << "Initiating a async task\n";
    std::future<int> fut = std::async(std::launch::async, get_ascii_sum, "ABCD");

    std::cout << "Performing some other task\n";

    std::cout << "Waiting using future, for result from time taking operation to be ready\n";
    auto res = fut.get();
    std::cout << "Result from time taking operation is ready, return value: " << res << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


