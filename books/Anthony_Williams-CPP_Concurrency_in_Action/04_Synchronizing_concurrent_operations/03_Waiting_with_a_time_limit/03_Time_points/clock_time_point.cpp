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


4.3.3 Time points

	Represented by std::chrono::time_point<> class template
	Template parameter
		First	clock it refers to
		Second	units of measurement (a specialization of std::chrono::duration<>)
		
	The value of a time point is the length of time (in multiples of the specified duration) since a specific point in time called the epoch of the clock.
	You can get the time_since_epoch() for a given time_point.
	
	You can add durations and subtract durations from instances of std::chrono:: time_point<> to produce new time points
	
	time points associated with the system clock can be obtained by converting from time_t using the std::chrono::system_clock::to_time_point()
	
	Recommended way to wait for condition variables with a time limit if you’re not passing a predicate to wait
	
	while(!done) {
		if(cv.wait_until(lk,timeout)==std::cv_status::timeout)
		break;
	}
	
	Drawback of wait_for
	If you use wait_for() in a loop, you might end up waiting almost the full length of time before a spurious wakeup, and the next time through the wait time starts again. This may repeat any number of times, making the total wait time unbounded.
	
**********/

#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>

void halt_for_seconds(uint32_t sec) {
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int main() {
    {
        std::cout << "=== system_clock ===\n";
        auto start_tp   = std::chrono::system_clock::now();
        
        auto epoch_time = start_tp.time_since_epoch();

        std::cout << "Time since epoch:\n";
        
        auto hr = std::chrono::duration_cast<std::chrono::hours>(epoch_time);
        std::cout << "hours elapsed " << hr.count() << '\n';

        auto min = std::chrono::duration_cast<std::chrono::minutes>(epoch_time);
        std::cout << "minutes elapsed " << min.count() << '\n';

        auto sec = std::chrono::duration_cast<std::chrono::seconds>(epoch_time);
        std::cout << "seconds elapsed " << sec.count() << '\n';

        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(epoch_time);
        std::cout << "milli seconds elapsed " << msec.count() << '\n';
        
        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(epoch_time);
        std::cout << "micro seconds elapsed " << usec.count() << '\n';  

        auto five_min_ahead = std::chrono::system_clock::now() + std::chrono::minutes(5);
        auto five_min_ahead_time = std::chrono::system_clock::to_time_t(five_min_ahead);
        std::cout << "Time after five min is " << std::put_time(std::localtime(&five_min_ahead_time), "%F %T") << '\n';

    }

    {
        std::cout << "\n=== system_clock ===\n";
        auto start_tp   = std::chrono::system_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::system_clock::now();

        auto durt = end_tp - start_tp;
        
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(durt);
        std::cout << "seconds elapsed " << sec.count() << '\n';

        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(durt);
        std::cout << "milli seconds elapsed " << msec.count() << '\n';
        
        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(durt);
        std::cout << "micro seconds elapsed " << usec.count() << '\n';  

    }
    
    {
        std::cout << "\n=== steady_clock ===\n";
        auto start_tp   = std::chrono::steady_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::steady_clock::now();

        auto durt = end_tp - start_tp;
        
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(durt);
        std::cout << "seconds elapsed " << sec.count() << '\n';

        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(durt);
        std::cout << "milli seconds elapsed " << msec.count() << '\n';
        
        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(durt);
        std::cout << "micro seconds elapsed " << usec.count() << '\n';  
        
    }
    

    {
        std::cout << "\n=== high_resolution_clock ===\n";
        auto start_tp   = std::chrono::high_resolution_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::high_resolution_clock::now();

        auto durt = end_tp - start_tp;
        
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(durt);
        std::cout << "seconds elapsed " << sec.count() << '\n';

        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(durt);
        std::cout << "milli seconds elapsed " << msec.count() << '\n';
        
        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(durt);
        std::cout << "micro seconds elapsed " << usec.count() << '\n';  
        
    }
    
    return 0;
}

/*****
    END OF FILE
**********/


