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


4.2.3 Making (std::)promises

	std::promise<T> provides a means of setting a value (of type T) that can later be read through an associated std::future<T> object.
	The waiting thread could block on the future, while the thread providing the data could use the promise to set the associated value and make the future ready.
	
	Get the std::future object associated with a given std::promise by calling the get_future() member function
	The value of the promise is set using the set_value() member function
	If you destroy the std::promise without setting a value, an exception is stored instead.

**********/

#include <iostream>
#include <future>
#include <string>
#include <thread>
#include <chrono>


void get_ascii_sum(std::string str, std::promise<int> prom_val) {
    int res = 0;
    int i   = 0;
    std::cout << "Executing some time taking operation\n";
    for(auto & elem : str) {
        res += elem;

        ++i;
        std::cout << "Executing some time taking operation " << std::string(i, '.') << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    prom_val.set_value(res);

    return ;
}

int main() {
    std::cout << "Initiating a thread to perform a task\n";
    std::promise<int> prom_val;
    std::future<int> fut = prom_val.get_future();
    std::thread thr(get_ascii_sum, "ABCD", std::move(prom_val));

    std::cout << "Performing some other task\n";

    std::cout << "Waiting using future, for result from time taking operation to be ready\n";
    auto res = fut.get();
    std::cout << "Result from time taking operation is ready, return value: " << res << '\n';

    if(thr.joinable()) thr.join();

    return 0;
}

/*****
    END OF FILE
**********/


