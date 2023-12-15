/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/atomic/atomic_thread_fence
    https://en.cppreference.com/w/cpp/atomic/atomic
    https://en.cppreference.com/w/cpp/atomic/memory_order

5.3 Synchronizing operations and enforcing ordering

    For two threads, one of which is populating a data structure to be read by the second. 
    In order to avoid a problematic race condition, 
        the first thread sets a flag to indicate that the data is ready, 
        and the second thread doesn’t read the data until the flag is set.

    Example

    std::vector<int> data;
    std::atomic<bool> data_ready(false);

    void reader_thread() {
        while(!data_ready.load()) {
            std::this_thread::sleep(std::chrono::milliseconds(1));
        }
        std::cout<<”The answer=”<<data[0]<<”\n”;
    }

    void writer_thread() {
        data.push_back(42);
        data_ready=true;
    }

    The required enforced ordering comes from the operations on the std::atomic<bool> variable, data_ready;, they provide the necessary ordering by virtue of the memory model relations happens-before and synchronizes-with.
    Because happens-before is transitive, the write to the data happens before the write to the flag, which happens before the read of the true value from the flag, which happens before the read of the data, and you have an enforced ordering.

5.3.5 Fences
	operations that enforce memory-ordering constraints without modifying any 
        data and are typically combined with atomic operations that use the memory_order_relaxed ordering constraints

	Fences are global operations and affect the ordering of other atomic operations in the thread that executed the fence
	Also called memory barriers, and they get their name because they put a line in the code that certain operations can’t cross

	As you may recall from section 5.3.3, relaxed operations on separate variables can usually be freely reordered by the compiler or the hardware.
	Fences restrict this freedom and introduce happens-before and synchronizes-with relationships that weren’t present before.	

	NOTE: Both fences are necessary: you need a release in one thread and an acquire in another to get a synchronizeswith relationship.


	General idea with fences:
	if an acquire operation sees the result of a store that takes place after a release fence, the fence synchronizes with that acquire operation; and 
	if a load that takes place before an acquire fence sees the result of a release operation, the release operation synchronizes with the acquire fence.

	The presence or absence of a fence doesn’t affect any enforced orderings on happens-before relationships that exist because of other atomic operations.

**********/

#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>

std::atomic<bool>   x, y;
std::atomic<int>    val;

void correct_write_x_then_y() {
    x.store(true, std::memory_order_relaxed);
    /*  It’s only when the fence comes between the store to x and the store to y 
        that it imposes an ordering     */
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    while(not y.load(std::memory_order_relaxed));
    std::atomic_thread_fence(std::memory_order_acquire);
    if(x.load(std::memory_order_relaxed)) {
        ++val;
    }
}

void incorrect_write_x_then_y() {
    std::atomic_thread_fence(std::memory_order_release);
    /*  These two operations are no longer separated by the fence and 
        so are no longer ordered*/
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

int main() {
    {
        std::cout << "=== correct use of fence ===\n";
        x = false;
        y = false;
        val = 0;

        std::thread wth(correct_write_x_then_y);
        std::thread rth(read_y_then_x);
        if(wth.joinable())  wth.join();
        if(rth.joinable())  rth.join();
        std::cout << "Guaranteed that val will not be equal to zero, val: " << val << '\n';
        assert(0 != val);   // this is guaranteed to never fail
    }

    {
        std::cout << "=== incorrect use of fence ===\n";
        x = false;
        y = false;
        val = 0;

        std::thread wth(incorrect_write_x_then_y);
        std::thread rth(read_y_then_x);
        if(wth.joinable())  wth.join();
        if(rth.joinable())  rth.join();
        std::cout << "No Guarantee that val will not be equal to zero, val: " << val << '\n';
        assert(0 != val);   // this may fail
    }

    return 0;
}

/*****
Explanation
if a load that takes place before the acquire fence sees a value written by a store that takes place after the release fence, the release fence synchronizes with the acquire fence

The release fence synchronizes with the acquire fence because the load from y before acquire fence reads the value stored after the release fence.
This causes synchronizes with relationship
This means that the store to x at happens before the load from x, so the value read must be true and the assert at won’t fire.

*****/


/*****
    END OF FILE
**********/


