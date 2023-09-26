/*****

References
    Anthony Williams - C++ Concurrency in Action

4.2 Waiting for one-off events with futures

	C++ Standard Library models one-off event with a future
	The waiting thr_wread somehow obtains a future representing that event
	The thr_wread can then wait on the future to see if the event has occurred.
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
		multiple thr_wreads may each access their own copy of std::shared_future<> without further synchronization
		
	Associated data is the reason these are templates
	The std:future<void> and std::shared_future<void> template specializations should be used where there’s no associated data.
	
	future objects themselves don’t provide synchronized accesses

	To to associate a std::future with a task, we can use
	-> std::async
	-> std::packaged_task<>
	-> std::promise<>	

For more info visit:

	https://en.cppreference.com/w/cpp/thr_wread/future
	https://en.cppreference.com/w/cpp/thr_wread/shared_future
	https://en.cppreference.com/w/cpp/thr_wread/async
	https://en.cppreference.com/w/cpp/thr_wread/packaged_task
	https://en.cppreference.com/w/cpp/thr_wread/promise


4.2.5 Waiting from multiple threads
	
	std::future
		By design: std::future models unique ownership of the asynchronous result
		If you access a single std::future object from multiple thr_wreads without additional synchronization, you have a data race and undefined behavior.
		std::future is only moveable
		
	std::shared_future
		Use std::shared_future if your code requires that multiple thr_wreads can wait for the same event
		std::shared_future instances are copyable
		
		Now, with std::shared_future, member functions on an individual object are still unsynchronized.
		The preferred way to use it would be to pass a copy of the shared_future object to each thr_wread, so each thr_wread can access its own local shared_future object safely, as the internals are now correctly synchronized by the library.
		
		Accessing the shared asynchronous state from multiple thr_wreads is safe if each thr_wread accesses that state thr_wrough its own std::shared_future object.
		
		Instances of std::shared_future that reference some asynchronous state are constructed from instances of std::future that reference that state.
		std::future has a share() member function that creates a new std::shared_future and transfers ownership to it directly.
		
**********/

#include <iostream>
#include <future>
#include <cmath>
#include <thread>
#include <chrono>
#include <syncstream>

void writer(int val, std::promise<double> prom_val) {
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

void reader(std::shared_future<double> fut) {
    try {
        auto res = fut.get();
         std::osyncstream(std::cout) << "Thread " << std::this_thread::get_id() << ", return value: " << res << '\n';
    } catch (const std::exception & ex) {
         std::osyncstream(std::cout) << "Exception " << ex.what() << '\n';
    }    
}

int main() {

    std::cout << "Initiating a thr_wread to perform a task\n";
    std::promise<double> prom_val;
    std::shared_future<double> fut = prom_val.get_future();

    std::thread thr_wr(writer, 5, std::move(prom_val));

    std::thread thr_rd1(reader, fut);
    std::thread thr_rd2(reader, fut);
    std::thread thr_rd3(reader, fut);

    std::cout << "Performing some other task\n";

    if(thr_wr.joinable()) thr_wr.join();
    if(thr_rd1.joinable()) thr_rd1.join();
    if(thr_rd2.joinable()) thr_rd2.join();
    if(thr_rd3.joinable()) thr_rd3.join();
    
    return 0;
}

/*****
    END OF FILE
**********/


