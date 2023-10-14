/*****

References
    Anthony Williams - C++ Concurrency in Action

	https://en.cppreference.com/w/cpp/thread/barrier
	https://en.cppreference.com/w/cpp/thread/barrier
	
	https://www.modernescpp.com/index.php/barrieres-in-c-20/
	https://www.modernescpp.com/index.php/barriers-in-c-20/
	

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.
	
4.4.7 barrieres and barriers

	NOTE: From Concurrency TS
		std::experimental::barrier has been merged to std C++20 as std::barrier
		std::experimental::barrier and std::experimental::flex_barrier has been merged to std C++20 as std::barrier
	
	Barrier
		A barrier is a reusable synchronization component used for internal synchronization between a set of threads.
		Each thread can only arrive at the barrier once per cycle.
		When threads arrive at the barrier, they block until all of the threads involvedhave arrived at the barrier, at which point they are all released. The barrier can then be reused.
		
		A barrier is helpful for managing repeated tasks by multiple threads

4.4.9 A basic barrier
	
	Construct a barrier with a count specifying the number of threads involved in the synchronization group.
	As each thread is done with its processing, it arrives at the barrier and waits for the rest of the group by calling arrive_and_wait on the barrier object. 
	When the last thread in the group arrives, all the threads are released, and the barrier is reset. 
	The threads in the group can then resume their processing and either process the next data item or proceed with the next stage of processing, as appropriate.
	
	A thread cannot wait for a barrier to be ready unless it is one of the threads in the synchronization group.
	Threads can explicitly drop out of the group by calling arrive_and_drop on the barrier, in which case that thread cannot wait for the barrier to be ready anymore, and the count of threads that must arrive in the next cycle is one less than the number of threads that had to arrive in the current cycle.
	
	Constants
		max [static]		the maximum value of expected count supported by the implementation

	Member functions
		arrive				arrives at barrier and decrements the expected count
		wait				blocks at the phase synchronization point until its phase completion step is run
		arrive_and_wait		arrives at barrier and decrements the expected count by one, then blocks until current phase completes
		arrive_and_drop		decrements both the initial expected count for subsequent phases and the expected count for current phase by one	


	Completion function
		There is an additional constructor that takes a completion function, as well as a thread count. 
		A std::barrier enables you to execute a function in the so-called completion step.
		Immediately after the counter becomes zero, the so-called completion step starts.
		In this completion step, a completion function is invoked.
		The completion step performs the following steps:
			All threads are blocked.
			An arbitrary thread is unblocked and executes the callable.
			If the completion step is done, all threads are unblocked.

		This provides
			a means of specifying a chunk of code that must be run serially
			a means of changing the number of threads that must arrive at the barrier for the next cycle
		
		
**********/

#include <iostream>
#include <thread>
#include <barrier>
#include <chrono>
#include <array>
#include <algorithm>
#include <syncstream>

void reader() {
    std::osyncstream(std::cout) << "Inside reader\n";
}

std::barrier barrier_done(3, reader);

void writer() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier_done.arrive();
}



void display_coll(const auto & coll) {
    for(const auto & elem : coll) {
        std::osyncstream(std::cout) << elem << ' ';
    }
    std::osyncstream(std::cout) << '\n';
}

std::array<int, 15> arr{0};
std::barrier  arr_barrier(3);

void set_and_display(int start, int end) {
    for(int i = start; i < end; ++i) {
        arr[i] = i;
    }
    arr_barrier.arrive_and_wait();
    std::osyncstream(std::cout) << "writer thread " << std::this_thread::get_id() << " done\n";
    display_coll(arr);
    
    std::for_each(arr.begin()+start, arr.begin()+end, [](auto &elem){ elem *= 2; });
    arr_barrier.arrive_and_wait();
    std::osyncstream(std::cout) << "writer thread " << std::this_thread::get_id() << " done\n";
    display_coll(arr);    
}

int main() {
   
    {
        std::osyncstream(std::cout) << "=== std::barrier count_down and wait ===\n";

        std::thread thr1(writer); thr1.detach();
        std::thread thr2(writer); thr2.detach();
        std::thread thr3(writer); thr3.detach();

        //barrier_done.wait();
    }


    {
        std::osyncstream(std::cout) << "\n=== std::barrier arrive_and_wait ===\n";

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



