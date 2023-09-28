/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/chrono

4.3 Waiting with a time limit
	In some cases you may want to put a limit on how long you wait for an event from another thread.
	
	Two types of timeouts
		1. duration-based timeout
			wait for a specific amount of time
			variants that handle this have a _for suffix
			
		2. absolute timeout
			wait until a specific point in time
			variants that handle this have an _until suffix
		
	For example, std::condition_variable has two overloads of the wait_for() member function and two overloads of the wait_until()
	
	template< class Rep, class Period >
	std::cv_status wait_for(	std::unique_lock<std::mutex>& lock,
								const std::chrono::duration<Rep, Period>& rel_time);
								
	template< class Rep, class Period, class Predicate >
	bool wait_for(	std::unique_lock<std::mutex>& lock,
					const std::chrono::duration<Rep, Period>& rel_time,
					Predicate stop_waiting);

	Duration-based waits are done with instances of std::chrono::duration<>.
	The wait functions all return a status to indicate whether the wait timed out or the waited-for event occurred.



4.3.4 Functions that accept timeouts

	Two functions that handle this
	
	1. std::this_thread::sleep_for()
		sleep_for()		makes sense where something must be done periodically, and the elapsed time is what matters
		sleep_until()	allows you to schedule the thread to wake at a particular point in time
		
	The functions from the C++ Standard Library that can accept timeouts
	
	============================================================================================================
	Class/Namespace				Functions					Return Values
	============================================================================================================
	std::this_thread			sleep_for(duration)						
						sleep_until(time_point)
	------------------------------------------------------------------------------------------------------------
			
	std::condition_variable or		wait_for(lock,duration)				std::cv_status::timeout
	std::condition_variable_any		wait_until(lock,time_point)			std::cv_status::no_timeout
											
						wait_for(lock,duration,predicate)		bool—the return value
						wait_until(lock,time_point,predicate)		of the predicate when woken
	------------------------------------------------------------------------------------------------------------
	std::timed_mutex,			try_lock_for(duration)				bool
	std::recursive_timed_mutex or		try_lock_until(time_point)			true  if the lock was acquired,
	std::shared_timed_mutex									false otherwise
	------------------------------------------------------------------------------------------------------------
	std::shared_timed_mutex			try_lock_shared_for(duration)			bool
						try_lock_shared_until(time_point)		true if the lock was acquired,
												false otherwise
	------------------------------------------------------------------------------------------------------------
	std::unique_lock<TimedLockable>		N/A—owns_lock() on the 
						newly constructed object
	unique_lock(lockable, duration)		returns
	unique_lock(lockable,time_point)	true if the lock was acquired
						false otherwise
											
						try_lock_for(duration)				bool
						try_lock_until(time_point)			true if the lock was acquired,
												false otherwise
	------------------------------------------------------------------------------------------------------------
	std::shared_lock<Shared-TimedLockable>	N/A—owns_lock() on the 
						newly constructed object
	shared_lock(lockable,duration)		returns
	shared_lock(lockable,time_point)	true if the lock was acquired
						false otherwise

						try_lock_for(duration)				bool
						try_lock_until(time_point)			true if the lock was acquired,
												false otherwise
	-----------------------------------------------------------------------------------------------------------
	std::future<ValueType>			wait_for(duration)				std::future_status::timeout
												if the wait timed out
	std::shared_future<Value-Type>		wait_until(time_point)				std::future_status::ready
												if the future is ready														     std::future_status::deferred									if the future holds a deferred function that hasn’t yet started
	===========================================================================================================

**********/

#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::vector<int>        gvec;
std::mutex              gvec_mutex;
std::condition_variable gvec_conv;

void writer(int no_elems) {
    int i = 0;
    while(i++ < no_elems) {
        std::cout << "Inside writer " << i << '\n';
        {
            std::unique_lock    ulock(gvec_mutex);
            gvec.push_back(i);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        gvec_conv.notify_one();
    }
}

void reader(int no_elems) {
    int i = 0;
    while(i++ < no_elems) {
        auto timeout = std::chrono::steady_clock::now() 
                        + std::chrono::seconds(1);
        std::unique_lock       ulock(gvec_mutex);

	// this may timeout after 1 sec if writer has not informed before that time point
	if(std::cv_status::timeout == gvec_conv.wait_until(ulock, timeout)) {
		std::cout << "Wait for data timeout\n";
	} else {

		int val = gvec.front();
		gvec.erase(gvec.begin());
		std::cout << "Inside reader value is " << val << '\n'; 

	}

	ulock.unlock();

    }
}

int main() {
    int no_elems = 10;

    std::thread wrt(writer, no_elems);
    wrt.detach();

    std::thread rdt(reader, no_elems);
    rdt.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}

/*****
    END OF FILE
**********/


