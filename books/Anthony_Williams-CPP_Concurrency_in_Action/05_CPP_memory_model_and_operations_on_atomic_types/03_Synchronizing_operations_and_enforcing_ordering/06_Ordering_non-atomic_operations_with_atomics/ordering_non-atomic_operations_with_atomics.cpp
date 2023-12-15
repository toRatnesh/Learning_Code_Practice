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

5.3.6 Ordering non-atomic operations with atomics
    We may use atomic operations along with non-atomic to enforce ordering on non-atomic operation

**********/

#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>

bool    x = false;
std::atomic<bool>   y;
std::atomic<int>    val;

void correct_write_x_then_y() {
    x = true;
    /*  It’s only when the fence comes between the assign to x and the store to y 
        that it imposes an ordering     */
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    while(not y.load(std::memory_order_relaxed));
    std::atomic_thread_fence(std::memory_order_acquire);
    if(x) {
        ++val;
    }
}

void incorrect_write_x_then_y() {
    std::atomic_thread_fence(std::memory_order_release);
    /*  These two operations are no longer separated by the fence and 
        so are no longer ordered*/
    x = true;
    y.store(true, std::memory_order_relaxed);
}

int main() {

        std::cout << "=== Ordering non-atomic operations with atomics ===\n";
    {
	std::cout << "=== correct use ===\n";
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
	std::cout << "=== incorrect use ===\n";

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

    The fences still provide an enforced ordering of the store to x and the store to y, 
    and the load from y and the load from x, 
    and there’s still a happens-before relationship between the store to x and the load from x, 
    so the assert still won’t fire.

    The fences enforce an ordering on the operations on x, once the reading thread has seen the stored value of y
    This enforced ordering means that there’s no data race on x

*****/

/*****
    END OF FILE
**********/


