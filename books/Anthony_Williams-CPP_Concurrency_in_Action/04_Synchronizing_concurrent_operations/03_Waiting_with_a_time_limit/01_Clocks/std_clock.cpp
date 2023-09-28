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

4.3.1 Clocks
	
	A clock is a class that provides four distinct pieces of information:
	->	The time now
	->	The type of the value used to represent the times obtained from the clock
	->	The tick period of the clock
	->	Whether or not the clock ticks at a uniform rate and is therefore considered to be a steady clock
	
	The current time of a clock can be obtained by calling the now() static member function for that clock class
	auto time_now = std::chrono::system_clock::now();
	
	The type of the time points for a particular clock is specified by the time_point member typedef
	The return type of some_clock::now() is some_clock::time_point
	
	If a clock ticks at a uniform rate (whether or not that rate matches the period) and can’t be adjusted, the clock is said to be a steady clock.
	The is_steady static data member of the clock class is true if the clock is steady, and false otherwise.
	
	Typically, std::chrono::system_clock will not be steady
	Steady clocks are important for timeout calculations, so the C++ Standard Library provides one in the form of std::chrono::steady_clock
	
	std::chrono::high_resolution_clock, which provides the smallest possible tick period (and thus the highest possible resolution) of all the library-supplied clocks. It may be a typedef to one of the other clocks.

**********/

#include <iostream>
#include <chrono>
#include <iomanip>

int main() {

    {
        std::cout << "=== system_clock ===\n";
        auto start_tp = std::chrono::system_clock::now();
        auto start_time = std::chrono::system_clock::to_time_t(start_tp);
        std::cout << "Time " << std::put_time(std::localtime(&start_time), "%F %T.\n");

        std::cout << "std::chrono::system_clock is " << (std::chrono::system_clock::is_steady ? "steady" : "non steady") << '\n'; 
    }
    
    {
        std::cout << "\n=== steady_clock ===\n";
        auto start_tp = std::chrono::steady_clock::now();

        std::cout << "std::chrono::steady_clock is " << (std::chrono::steady_clock::is_steady ? "steady" : "non steady") << '\n';
    }
    

    {
        std::cout << "\n=== high_resolution_clock ===\n";
        auto start_tp = std::chrono::high_resolution_clock::now();

        std::cout << "std::chrono::high_resolution_clock is " << (std::chrono::high_resolution_clock::is_steady ? "steady" : "non steady") << '\n';

    }
    
    return 0;
}

/*****
    END OF FILE
**********/


