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

5.3.2 The happens-before relationship

The happens-before and strongly-happens-before relationships
	basic building blocks of operation ordering in a program; 
	it specifies which operations see the effects of which other operations
	
For a single thread,
	if one operation (A) occurs in a statement prior to another (B) in the source code, then A happens before B, and A strongly-happens-before B
	
For multi thread,
	if operation A in one thread synchronizes with operation B in another thread, then A inter-thread happens before B
	It’s also a transitive relation: if A inter-thread happens before B and B inter-thread happens before C, then A inter-thread happens before C

Inter-thread happens-before also combines with the sequenced-before relation:
	if operation A is sequenced before operation B, and operation B inter-thread happens before operation C, then A inter-thread happens before C
	if A synchronizes with B and B is sequenced before C, then A inter-thread happens before C

Strongly-happens-before relationship
	if operation A synchronizes-with operation B, or operation A is sequenced-before operation B, then A strongly-happens-before B
	Transitive ordering: if A strongly-happens before B, and B strongly-happens-before C, then A strongly-happens-before C

Difference
	operations tagged with memory_order_consume 
		participate in inter-thread-happens-before relationships (and thus happens-before relationships), 
		but not in strongly-happens-before relationships


**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

int                 data;
std::atomic_bool    data_from_a_ready;
std::atomic_bool    data_from_b_ready;

void thread_a() {
    std::cout << "Demostrating transitive ordering happens-before relationship\n";
    
    data = 11;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    data_from_a_ready = true;
}

void thread_b() {
    while(not data_from_a_ready.load()) {
        std::cout << "Waiting for data from thread a ...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Data from thread a " << data << '\n';

    data = 12;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    data_from_b_ready = true;
}

void thread_c() {
    while(not data_from_b_ready.load()) {
        std::cout << "Waiting for data from thread b ...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Data from thread b " << data << '\n';
}

int main() {

    std::thread tha(thread_a);
    std::thread thb(thread_b);
    std::thread thc(thread_c);

    tha.join();
    thb.join();
    thc.join();

    return 0;
}

/*****
    END OF FILE
**********/


