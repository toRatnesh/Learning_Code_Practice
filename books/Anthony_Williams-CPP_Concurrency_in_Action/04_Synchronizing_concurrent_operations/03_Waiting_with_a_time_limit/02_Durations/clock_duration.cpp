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

	
4.3.2 Durations

	Handled by the std:: chrono::duration<> class template
	Template parameter
		First	- type of the representation (such as int, long, or double)
		Second	- fraction specifying how many seconds each unit of the duration represents
		
	Example
		A count of milliseconds stored in a double is
		std::chrono::duration<double, std::ratio<1, 1000>>
		because each millisecond is 1/1000th of a second
	
		A number of minutes stored in a short is
		std::chrono::duration<short,std::ratio<60,1>>
		because there are 60 seconds in a minute		
		
		
	The Standard Library provides a set of predefined typedefs in the std::chrono namespace for various durations: nanoseconds, microseconds, milliseconds, seconds, minutes, and hours.
	
	Predefined literal suffix operators for durations in the std::chrono_literals namespace	(since C++14)
	Example
	using namespace std::chrono_literals;
	auto one_day		= 24h;
	auto half_an_hour	= 30min;
	auto max_time_between_messages = 30ms;
	
	Conversion between durations is implicit where it does not require truncation of the value
	Explicit conversions can be done with std::chrono::duration_cast<>; the result is truncated rather than rounded
	std::chrono::milliseconds ms(54802);
	std::chrono::seconds s= std::chrono::duration_cast<std::chrono::seconds>(ms);	// s will have a value of 54
	
	Durations support arithmetic
	
	The count of the number of units in the duration can be obtained with the count() member function.
	
	Duration-based waits are done with instances of std::chrono::duration<>.
	The wait functions all return a status to indicate whether the wait timed out or the waited-for event occurred.
	
	The time for a duration-based wait is measured using a steady clock internal to the library

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
        std::chrono::duration<double, std::ratio<60, 1>>    mins(2);
        std::chrono::duration<double, std::ratio<1, 1000>>  ms(2);

        std::cout << "mins.count() " << mins.count() << '\n';
        std::cout << "ms.count() " << ms.count() << '\n';

        std::chrono::duration<double, std::ratio<1, 1000>>  ms2(mins);
        std::cout << "ms2.count() " << ms2.count() << '\n';
    }

    {
        std::cout << "\n=== system_clock ===\n";
        auto start_tp   = std::chrono::system_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::system_clock::now();
        std::chrono::duration<double> sec_elp = end_tp - start_tp;
        std::cout << "Seconds elapsed " << sec_elp.count() << '\n';

        std::chrono::duration<double, std::milli> msec_elp = end_tp - start_tp;
        std::cout << "Milli seconds elapsed " << msec_elp.count() << '\n';
        
        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to us) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to us) micro seconds elapsed " << usec.count() << '\n';
        }

    }
    
    {
        std::cout << "\n=== steady_clock ===\n";
        auto start_tp   = std::chrono::steady_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::steady_clock::now();
        std::chrono::duration<double> sec_elp = end_tp - start_tp;
        std::cout << "Seconds elapsed " << sec_elp.count() << '\n';

        std::chrono::duration<double, std::milli> msec_elp = end_tp - start_tp;
        std::cout << "Milli seconds elapsed " << msec_elp.count() << '\n';
        
        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to us) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to us) micro seconds elapsed " << usec.count() << '\n';
        }

    }
    

    {
        std::cout << "\n=== high_resolution_clock ===\n";
        auto start_tp   = std::chrono::high_resolution_clock::now();
        halt_for_seconds(2);
        auto end_tp     = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sec_elp = end_tp - start_tp;
        std::cout << "Seconds elapsed " << sec_elp.count() << '\n';

        std::chrono::duration<double, std::milli> msec_elp = end_tp - start_tp;
        std::cout << "Milli seconds elapsed " << msec_elp.count() << '\n';
        
        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp);
        std::cout << "(Using duration_cast) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(sec_elp);
        std::cout << "(Using duration_cast from sec to us) micro seconds elapsed " << usec.count() << '\n';            
        }

        {
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to ms) milli seconds elapsed " << msec.count() << '\n';

        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(msec_elp);
        std::cout << "(Using duration_cast from ms to us) micro seconds elapsed " << usec.count() << '\n';
        }
    }
    
    return 0;
}

/*****
    END OF FILE
**********/


