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


4.2.4 Saving an exception for the future

	If the function call invoked as part of std::async throws an exception, that exception is stored in the future in place of a stored value, the future becomes ready, and a call to get() rethrows that stored exception.
	
	The same happens if you wrap the function in a std::packaged_task.
	
	std::promise provides the same facility.
	To store an exception rather than a value, you call the set_exception() member function rather than set_value().
	This uses std::current_exception() to retrieve the thrown exception.
	
	Another way to store an exception in a future is to destroy the std::promise or std::packaged_task associated with the future without calling either of the set functions on the promise or invoking the packaged task.
	
	In either case, the destructor of std::promise or std::packaged_task will store a std::future_error exception with an error code of std::future_errc::broken_promise in the associated state if the future isn’t already ready.
	
	
	std::future Limitation
	std::future has its limitations, not the least of which being that only one thread can wait for the result.
	If you need to wait for the same event from more than one thread, you need to use std::shared_future instead.
	
**********/

#include <iostream>
#include <future>
#include <cmath>
#include <thread>
#include <chrono>


void get_sqrt(int val, std::promise<double> prom_val) {
    double res = 0;
    std::cout << "Executing some time taking operation\n";
    try {
        if(val > 0) {
            res = std::sqrt(val);
            prom_val.set_value(res);
        } else {
            throw std::logic_error("can not find sqrt of -ve number");
        }
    } catch(...) {
        prom_val.set_exception(std::current_exception());
    }

    return ;
}

int main() {

    {
        std::cout << "Initiating a thread to perform a task\n";
        std::promise<double> prom_val;
        std::future<double> fut = prom_val.get_future();
        std::thread thr(get_sqrt, 5, std::move(prom_val));

        std::cout << "Performing some other task\n";

        std::cout << "Waiting using future, for result from time taking operation to be ready\n";
        try {
            auto res = fut.get();
            std::cout << "Result from time taking operation is ready, return value: " << res << '\n';
        } catch (const std::exception & ex) {
            std::cout << "Exception " << ex.what() << '\n';
        }

        if(thr.joinable()) thr.join();
    }
    std::cout << '\n';

    {
        std::cout << "Initiating a thread to perform a task\n";
        std::promise<double> prom_val;
        std::future<double> fut = prom_val.get_future();
        std::thread thr(get_sqrt, -4, std::move(prom_val));

        std::cout << "Performing some other task\n";

        std::cout << "Waiting using future, for result from time taking operation to be ready\n";
        try {
            auto res = fut.get();
            std::cout << "Result from time taking operation is ready, return value: " << res << '\n';
        } catch (const std::exception & ex) {
            std::cout << "Exception: " << ex.what() << '\n';
        }

        if(thr.joinable()) thr.join();
    }

    return 0;
}

/*****
    END OF FILE
**********/


