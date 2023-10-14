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

4.4.8 A basic latch 
	specify the initial counter value as the one and only argument to the constructor

	Constants
		max[static]			the maximum value of counter supported by the implementation

	Member functions
		count_down			decrements the counter in a non-blocking manner
		try_wait			tests if the internal counter equals zero
		wait				blocks until the counter reaches zero
		arrive_and_wait		decrements the counter and blocks until it reaches zero

**********/

#include <iostream>
#include <thread>
#include <latch>
#include <chrono>
#include <array>
#include <algorithm>
#include <syncstream>

std::latch latch_done(3);

void writer() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "writer thread " << std::this_thread::get_id() << " done\n";
    latch_done.count_down();
}

void reader() {
    std::osyncstream(std::cout) << "Inside reader\n";
}

void display_coll(const auto & coll) {
    for(const auto & elem : coll) {
        std::osyncstream(std::cout) << elem << ' ';
    }
    std::osyncstream(std::cout) << '\n';
}

std::array<int, 15> arr{0};
std::latch  arr_latch(3);

void set_and_display(int start, int end) {
    for(int i = start; i < end; ++i) {
        arr[i] = i;
    }
    arr_latch.arrive_and_wait();
    std::osyncstream(std::cout) << "writer thread " << std::this_thread::get_id() << " done\n";
    display_coll(arr);
}

int main() {
    
    {
        std::osyncstream(std::cout) << "=== std::latch count_down and wait ===\n";

        std::thread thr1(writer); thr1.detach();
        std::thread thr2(writer); thr2.detach();
        std::thread thr3(writer); thr3.detach();

        if(not latch_done.try_wait()) {
            std::osyncstream(std::cout) << "Latch is not ready yet\n";
        }

        latch_done.wait();
        reader();    
    }
    
    {
        std::osyncstream(std::cout) << "\n=== std::latch arrive_and_wait ===\n";

        std::thread thr1(set_and_display, 0, 5);    thr1.detach();
        std::thread thr2(set_and_display, 5, 10);   thr2.detach();
        std::thread thr3(set_and_display, 10, 15);  thr3.detach();        
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}

/*****
    END OF FILE
**********/



