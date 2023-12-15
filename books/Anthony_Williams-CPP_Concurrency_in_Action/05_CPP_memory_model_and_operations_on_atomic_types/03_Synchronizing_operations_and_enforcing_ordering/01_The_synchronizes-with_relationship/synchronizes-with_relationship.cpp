/*****

References
    Anthony Williams - C++ Concurrency in Action
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

5.3.1 The synchronizes-with relationship

    The synchronizes-with relationship is something that you can get only between operations on atomic types.
    if thread A stores a value and thread B reads that value, 
        there’s a synchronizes-with relationship between the store in thread A and the load in thread B


**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

int                 data;
std::atomic_bool    data_ready_flag;

void consumer() {
    while(not data_ready_flag.load()) {
	std::cout << "Waiting for data to be ready ...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Data is " << data << '\n';
}

void producer() {
    data = 56;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    data_ready_flag = true;
}

int main() {
    std::thread cth(consumer);
    std::thread pth(producer);
    
    pth.join();
    cth.join();

    return 0;
}


/*****

Explanation

The write of the data happens before the write to the data_ready_flag flag, and
the read of the flag happens before the read of the data.
When the value read from data_ready_flag is true, the write synchronizes with that read, creating a happens-before relationship.

Because happens-before is transitive,
the write to the data happens before the write to the flag,
which happens before the read of the true value from the flag,
which happens before the read of the data, and you have an enforced ordering

**********/

/*****
    END OF FILE
**********/


