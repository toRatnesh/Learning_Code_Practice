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

5.3.7 Ordering non-atomic operations
	If a non-atomic operation is sequenced before an atomic operation, 
        and that atomic operation happens before an operation in another thread, 
        the non-atomic operation also happens before that operation in the other thread.
	
	consider the simple spinlock mutex
	Although other mutex implementations will have different internal operations, the basic principle is the same: 
		lock() is an acquire operation on an internal memory location, and 
		unlock() is a release operation on that same memory location.

    Each of the synchronization mechanisms provide ordering guarantees in terms of the synchronizes-with relationship.

    The following are the synchronization relationships provided by these facilities:
        std::thread
        std::mutex, std::timed_mutex, std::recursive_mutex, std::recursive_timed_mutex
        std::shared_mutex, std::shared_timed_mutex
        std::promise, std::future AND std::shared_future
        std::packaged_task, std::future AND std::shared_future
        std::async, std::future AND std::shared_future
        std::experimental::future, std::experimental::shared_future AND CONTINUATIONS
        std::experimental::latch
        std::experimental::barrier
        std::experimental::flex_barrier
        std::condition_variable AND std::condition_variable_any

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class x_mutex {
    std::atomic_bool     flag{false};
    public:
    void lock() {
        while(flag.load(std::memory_order_acquire)) { }
        flag.store(true, std::memory_order_release);
    }
    void unlock() {
        flag.store(false, std::memory_order_release);
    }
};


int     data = 0;
x_mutex data_lock;

void increment_using_lock() {
    data_lock.lock();

    ++data;
    std::cout << std::this_thread::get_id() << ", value " << data << '\n';
    
    data_lock.unlock();
}

void increment() {
    ++data;
    std::cout << std::this_thread::get_id() << ", value " << data << '\n';
}


int main() {
    {
        std::vector<std::thread> vec;
        for(int i = 0; i < 10; ++i) {
            vec.push_back(std::thread(increment_using_lock));
        }

        for(auto & th : vec) {
            th.join();
        }
    }
    std::cout << '\n';
    data = 0;
    
    {
        std::vector<std::thread> vec;
        for(int i = 0; i < 10; ++i) {
            vec.push_back(std::thread(increment));
        }

        for(auto & th : vec) {
            th.join();
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/


