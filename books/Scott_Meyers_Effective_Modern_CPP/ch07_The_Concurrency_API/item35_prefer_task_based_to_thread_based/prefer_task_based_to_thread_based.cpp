/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/thread/thread
	https://en.cppreference.com/w/cpp/thread/async

Item 35: Prefer task-based programming to thread based

Two basic choices to run a function doAsyncWork asynchronously
1.	thread-based approach:	create a std::thread and run doAsyncWork on it
2.	task-based approach:	pass doAsyncWork to std::async, 
							the function object passed to std::async (e.g., doAsyncWork) is considered a task

The task-based approach is typically superior to its thread-based counterpart

If we want to access the returned value from doAsyncWork
With the thread-based invocation, there’s no straightforward way to get access to it.

The future returned from std::async offers the get function.
The get function is even more important if doAsyncWork emits an exception, because get provides access to that, too. 

With the thread-based approach, if doAsyncWork throws, the program dies (via a call to std::terminate).


task-based programming offers higher level of abstraction, It frees you from the details of thread management

The three meanings of “thread” in concurrent C++ software:
	1.	Hardware threads are the threads that actually perform computation.
		Contemporary machine architectures offer one or more hardware threads per CPU core.
		
	2.	Software threads (OS threads or system threads) are the threads that the operating system manages 
		across all processes and schedules for execution on hardware threads.

		It’s typically possible to create more software threads than hardware threads, 
		because when a software thread is blocked (e.g., on I/O or waiting for a mutex or condition variable), 
		throughput can be improved by executing other, unblocked, threads.
		
	3.	std::threads are objects in a C++ process that act as handles to underlying software threads.


Problem with thread-based
	.	Software threads are a limited resource. 
		If you try to create more than the system can provide, a std::system_error exception is thrown.
		
	.	Oversubscription:	There are more ready-to-run (i.e., unblocked) software threads than hardware threads.

std::async call shifts the thread management responsibility to the implementer of the C++ Standard Library

std::async, when called in this form (i.e., with the default launch policy—see Item 36), 
doesn’t guarantee that it will create a new software thread.
schedulers take advantage of that freedom if the system is oversubscribed or is out of threads

If you need, std::launch::async launch policy to std::async will ensure 
that the function you want to run really executes on a different thread

State-of-the-art thread schedulers employ system-wide thread pools to avoid oversubscription, 
and they improve load balancing across hardware cores through workstealing algorithms. 

The C++ Standard does not require the use of thread pools or work-stealing, and, to be honest, 
there are some technical aspects of the C++11 concurrency specification that make it more difficult to employ them.

situations where using threads directly may be appropriate:
	• You need access to the API of the underlying threading implementation
	• You need to and are able to optimize thread usage for your application.
	• You need to implement threading technology beyond the C++ concurrency API


Summary:
	•	The std::thread API offers no direct way to get return values from asynchronously run functions, 
		and if those functions throw, the program is terminated.
	•	Thread-based programming calls for manual management of 
		thread exhaustion, oversubscription, load balancing, and adaptation to new platforms. 
	•	Task-based programming via std::async with the default launch policy handles most of these issues for you.	

**********/

#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <exception>


void doAsyncWork(const std::string str) {

    if(str.empty()) {
        throw std::runtime_error("Empty string is passed");
    }

    std::cout << "Inside " << __func__ 
    << ", thread id " << std::this_thread::get_id() 
    << ", " << str << '\n';
}

int main() {
    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';

    auto fut1 = std::async(doAsyncWork, "using async without get");
    
    auto fut2 = std::async(doAsyncWork, "using async with get");
    if(fut2.valid()) {
        fut2.get();
    }

    std::thread th{doAsyncWork, "using thread"};
    if(th.joinable()) {
        th.join();
    }

    try {
        auto fut3 = std::async(doAsyncWork, "");
        fut3.get();              
    } catch (const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

    /*
    try {
        // ANY EXCEPTION FROM THREAD WILL NOT BE CAUGHT, INSTEAD TERMINATE WILL BE CALLED
        std::thread th{doAsyncWork, ""}; 
        if(th.joinable()) {
            th.join();
        }               
    } catch (const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }
    */

    return 0;
}

/*****
    END OF FILE
**********/

