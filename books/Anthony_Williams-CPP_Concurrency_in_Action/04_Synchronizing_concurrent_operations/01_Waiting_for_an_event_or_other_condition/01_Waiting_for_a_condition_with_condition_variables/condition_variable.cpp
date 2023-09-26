/*****

References
    Anthony Williams - C++ Concurrency in Action

4. Synchronizing concurrent operations

	Sometimes we need to synchronize actions on separate threads. 
	One thread might need to wait for another thread to complete a task before the first thread can complete its own.

	C++ Standard Library techniques to handle synchronization

		Condition variables
		Futures
		Latches				(since C++20)
		Barriers			(since C++20)

4.1 Waiting for an event or other condition

	If one thread is waiting for a second thread to complete a task, it has several options
	
	1. keep checking a flag in shared data (protected by a mutex)
	2. the waiting thread sleep for short periods between the checks using the std::this_thread::sleep_for()
	3. condition variable (preferred)

4.1.1 Waiting for a condition with condition variables

Condition variable
	Conceptually, a condition variable is associated with an event or other condition, and one or more threads can wait for that condition to be satisfied. 
	When a thread has determined that the condition is satisfied, it can then notify one or more of the threads waiting on the condition variable in order to wake them up and allow them to continue processing.

Two variants

	std::condition_variable<>			works with std::mutex
	std::condition_variable_any<>		may work with any mutex-like that meets the BasicLockable requirements

	A condition variable is always associated with a mutex.
	
	Because std::condition_variable_any is more general, there’s the potential for additional costs in terms of size, performance, or OS resources.
	Fundamentally, std::condition_variable::wait is an optimization over a busy-wait.

	
	notify_all()
		causes all the threads currently executing wait() to check the condition they’re waiting for

Using Condition variable
	Writer Thread
		Acquire mutex 
		Update data 
		Release mutex
		Notify condition variable (use notify_one() or notify_all() member funciton as per requirement)
		
	Reader Thread
		Acquire mutex with unique_lock (because we need to unlock and lock in between)
		call wait() on the std:: condition_variable, passing in the lock object and a lambda function that expresses the condition being waited for
		If the condition isn’t satisfied (the lambda function returned false), wait() unlocks the mutex and puts the thread in a blocked or waiting state
		After condition variable is notified by writer thread process the data
		Unlock mutex

Spurious wake and side effects
	When the waiting thread reacquires the mutex and checks the condition, if it isn’t in direct response to a notification from another thread, it’s called a spurious wake.
	Because the number and frequency of any such spurious wakes are by definition indeterminate.
	It isn’t advisable to use a function with side effects for the condition check. If you do so, you must be prepared for the side effects to occur multiple times.
	
NOTE: 
	If the waiting thread is going to wait only once, so when the condition is true it will never wait on this condition variable again, a condition variable might not be the best choice of synchronization mechanisms.
	In this scenario, a future might be more appropriate.

**********/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <chrono>

std::vector<int>        gvec;
std::mutex              gvec_mutex;
std::condition_variable gvec_conv;

void writer(int no_elems, bool for_all) {
    int i = 0;
    while(i++ < no_elems) {
        std::cout << "Inside writer " << i << '\n';
        {
            std::unique_lock    ulock(gvec_mutex);
            gvec.push_back(i);
        }
        if(for_all) {
            gvec_conv.notify_all();
        } else {
            gvec_conv.notify_one();
        }
        
        std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    }
}

void reader(int no_elems) {
    int i = 0;
    while(i++ < no_elems) {
        std::unique_lock       ulock(gvec_mutex);
        gvec_conv.wait(ulock, []{return not gvec.empty();});
        int val = gvec.front();
        gvec.erase(gvec.begin());
        ulock.unlock();

        std::cout << "Inside thread " << std::this_thread::get_id() << " reader value is " << val << '\n'; 
    }
}

int main() {
    int no_elems = 10;

    {
        /*
        std::thread wrt(writer, no_elems, false);
        wrt.detach();

        std::thread rdt(reader, no_elems);
        rdt.detach();
        */
    }


    {
        std::thread wrt(writer, no_elems, true);
        wrt.detach();

        std::thread rdt1(reader, no_elems/2);
        std::thread rdt2(reader, no_elems/2);

        rdt1.detach();
        rdt2.detach();

    }

    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}

/*****
    END OF FILE
**********/


