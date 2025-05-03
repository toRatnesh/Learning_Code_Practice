/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/thread/thread
    https://en.cppreference.com/w/cpp/thread/async

Item 38: Be aware of varying thread handle destructor behavior

a joinable std::thread corresponds to an underlying system thread of execution
A future for a non-deferred task has a similar relationship to a system thread
both std::thread objects and future objects can be thought of as handles to system threads

destruction of a joinable std::thread terminates your program
destructor for a future never causes program termination

shared state
	We’ll begin with the observation that a future is one end of a communications channel 
	through which a callee transmits a result to a caller.

	 ----------------                                    ----------------
	|                |future                std::promise|                |
	|     Caller     |<---------------------------------|    Callee      |
	|                |                      (typically) |                |
	 ----------------                                    ----------------

	But where is the callee’s result stored?
	it’s stored in a location outside both caller and callee objects
	This location is known as the shared state
	shared state is typically represented by a heap-based object, but 
	its type, interface, and implementation are not specified by the Standard
	Standard Library authors are free to implement shared states in any way they like
	
					     Shared State
	 ----------------                    -----------                            -----------------
	|                |future            |Callee's   |              std::promise|                 |
	|   Caller       |<-----------------|           |<-------------------------|    Callee       |
	|                |                  |Result     |               (typically)|                 |
	 ----------------                    -----------                            -----------------
	
	the behavior of a future’s destructor is determined by the shared state associated with the future
	
	•	The destructor for the last future referring to a shared state for a nondeferred task 
		launched via std::async blocks until the task completes. (amounts to implicit join on the underlying thread)
	•	The destructor for all other futures simply destroys the future object
		(amounts to implicit detach on the underlying thread)
		For deferred tasks for which this is the final future, it means that the deferred task will never run


	The exception to this normal behavior arises only for a future for which all of the following apply:

	•	It refers to a shared state that was created due to a call to std::async.
	•	The task’s launch policy is std::launch::async
	•	The future is the last future referring to the shared state
		For std::shared_futures, if other std::shared_futures refer to the same shared state as the future being destroyed, 
		the future being destroyed follows the normal behavior (i.e., it simply destroys its data members).

	Only when all of these conditions are fulfilled does a future’s destructor exhibit special behavior, 
	and that behavior is to block until the asynchronously running task completes.


std::packaged_task	
	std::packaged_task object prepares a function (or other callable object) for asynchronous execution 
	by wrapping it such that its result is put into a shared state. 
	A future referring to that shared state can then be obtained via std::packaged_task’s get_future function:
	
		int calcValue();							// func to run
		std::packaged_task<int()> pt(calcValue);	// wrap calcValue so it can run asynchronously
		auto fut = pt.get_future();					// get future for pt
		
	the future fut doesn’t refer to a shared state created by a call to std::async, so its destructor will behave normally
	
	std::packaged_tasks aren’t copyable
	
	when you have a future corresponding to a shared state that arose due to a std::packaged_task, 
	there’s usually no need to adopt a special destruction policy, 
	because the decision among termination, joining, or detaching will be made in the code
	
Summary
	•	Future destructors normally just destroy the future’s data members.
	•	The final future referring to a shared state for a non-deferred task launched via std::async blocks until the task completes.	

**********/

#include <iostream>
#include <thread>
#include <string>
#include <future>

void doAsyncWork(const std::string str) {

    std::cout << "Inside " << __func__ 
    << ", thread id " << std::this_thread::get_id() 
    << ", " << str << '\n';
}


int main() {

    std::cout << "Inside " << __func__ << ", thread id " << std::this_thread::get_id() << '\n';

    std::cout << "\n=== Executing 3 task with deferred policy and wihtout get, with get and shared_future ===\n";

    auto fut11 = std::async(std::launch::deferred, doAsyncWork, "using async with deferred and without get");
    
    auto fut12 = std::async(std::launch::deferred, doAsyncWork, "using async with deferred and get");
    if(fut12.valid()) {
        fut12.get();
    }

    std::shared_future<void>    sfut13;
    auto fut13 = std::async(std::launch::deferred, doAsyncWork, "using async with deferred and without get, future is assigned to shared_future");
    sfut13 = std::move(fut13);


    std::cout << "\n=== Executing 3 task with async policy and wihtout get, with get and shared_future ===\n";

    auto fut21 = std::async(std::launch::async, doAsyncWork, "using async with async and without get");

    auto fut22 = std::async(std::launch::deferred, doAsyncWork, "using async with async and get");
    if(fut22.valid()) {
        fut22.get();
    }

    std::shared_future<void>    sfut23;
    auto fut23 = std::async(std::launch::deferred, doAsyncWork, "using async with async and without get, future is assigned to shared_future");
    sfut23 = std::move(fut23);

    

    std::cout << "\n=== Executing 3 task with default policy and wihtout get, with get and shared_future ===\n";

    auto fut31 = std::async(doAsyncWork, "using async with default and without get");

    auto fut32 = std::async(doAsyncWork, "using async with default and get");
    if(fut32.valid()) {
        fut32.get();
    }

    std::shared_future<void>    sfut33;
    auto fut33 = std::async(doAsyncWork, "using async with default and without get, future is assigned to shared_future");
    sfut33 = std::move(fut33);

    std::cout << "\n=== Executing 2 packaged task with thread without get on future of tasks ===\n";

    std::packaged_task<void(const std::string)>     task11(doAsyncWork);
    auto tfut11 = task11.get_future();

    std::packaged_task<void(const std::string)>     task12(doAsyncWork);
    auto tfut12 = task12.get_future();

    std::thread     th_task11(std::move(task11), "using packaged task executed by thread and no call to get on future");
    std::thread     th_task12(std::move(task12), "using packaged task executed by thread and no call to get on future");

    try {
        if(th_task11.joinable()) {
            th_task11.detach();
        }

        if(th_task12.joinable()) {
            th_task12.join();
        }

    } catch(const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

    std::cout << "\n=== Executing 2 packaged task with thread with get on future of tasks before joining threads ===\n";

    std::packaged_task<void(const std::string)>     task21(doAsyncWork);
    auto tfut21 = task21.get_future();

    std::packaged_task<void(const std::string)>     task22(doAsyncWork);
    auto tfut22 = task22.get_future();

    std::thread     th_task21(std::move(task21), "using packaged task executed by thread and no call to get on future");
    std::thread     th_task22(std::move(task22), "using packaged task executed by thread and call to get on future");

    try {
        if(tfut21.valid()) {
            tfut21.get();
        }

        if(tfut22.valid()) {
            tfut22.get();
        }

        if(th_task21.joinable()) {
            th_task21.join();
        }

        if(th_task22.joinable()) {
            th_task22.detach();
        }

    } catch(const std::exception & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

    return 0;
}

/*****
    END OF FILE
**********/

