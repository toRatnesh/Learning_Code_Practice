/*****

References
    Anthony Williams - C++ Concurrency in Action

	https://en.cppreference.com/w/cpp/thread/latch
	https://en.cppreference.com/w/cpp/thread/barrier
	
	https://www.modernescpp.com/index.php/latches-in-c-20/
	https://www.modernescpp.com/index.php/barriers-in-c-20/
	

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.
	
4.4.7 Latches and barriers

	NOTE: From Concurrency TS
		std::experimental::latch has been merged to std C++20 as std::latch
		std::experimental::barrier and std::experimental::flex_barrier has been merged to std C++20 as std::barrier
	
	Latch
		A latch is a synchronization object that becomes ready when its counter is decremented to zero.
		It latches the output—once it is ready, it stays ready until it is destroyed. 
		A latch is thus a lightweight facility for waiting for a series of events to occur.
		
		A latch doesn’t care which threads decrement the counter—the same thread can decrement the counter single/multiple time(s).
		Latches are inherently simpler than barriers.
		
		A latch is useful for managing one task by multiple threads.
		
	Barrier
		A barrier is a reusable synchronization component used for internal synchronization between a set of threads.
		Each thread can only arrive at the barrier once per cycle.
		When threads arrive at the barrier, they block until all of the threads involvedhave arrived at the barrier, at which point they are all released. The barrier can then be reused.
		
		A barrier is helpful for managing repeated tasks by multiple threads

	Concurrent invocations of the member functions of a std::latch or a std::barrier are no data race.
	
**********/

#include <iostream>
#include <latch>
#include <barrier>

int main() {

    std::cout << "Max allowed latch count " << std::latch::max << '\n';
    std::cout << "Max allowed barrier count " << std::barrier<nullptr_t>::max << '\n';

    return 0;
}

/*****
    END OF FILE
**********/



