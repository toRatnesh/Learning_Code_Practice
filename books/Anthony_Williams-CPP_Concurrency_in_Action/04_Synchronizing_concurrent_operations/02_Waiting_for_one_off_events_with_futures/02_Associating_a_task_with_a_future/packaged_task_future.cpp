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


4.2.2 Associating a task with a future

	std::packaged_task<> ties a future to a function or callable object. 
	When the std::packaged_task<> object is invoked, it calls the associated function or callable object and makes the future ready, with the return value stored as the associated data.
	
	This can be used as a building block for thread pools.
	
	For callable return and parameters, types don’t have to match exactly; if the types are implicitly convertible.

	The std::packaged_task object is a callable object.
	
	After invocation the return value is stored as the asynchronous result in the std::future obtained from get_future().

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

template<typename Task>
void excute_task(Task task, std::string str) {
    task(str);
}

int main() {
    std::cout << "Initiating a task using std::packaged_task\n";
    std::packaged_task<int(std::string)> task(get_ascii_sum);
    auto fut = task.get_future();
    
    excute_task(std::move(task), std::string("ABCD"));
    
    std::cout << "Performing some other task\n";

    std::cout << "Waiting using future, for result from time taking operation to be ready\n";
    auto res = fut.get();
    std::cout << "Result from time taking operation is ready, return value: " << res << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


