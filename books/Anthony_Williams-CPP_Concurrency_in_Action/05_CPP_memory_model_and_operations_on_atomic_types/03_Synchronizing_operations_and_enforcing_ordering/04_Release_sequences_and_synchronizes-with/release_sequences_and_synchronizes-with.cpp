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

5.3.4 Release sequences and synchronizes-with
	If the store is tagged with memory_order_release, memory_order_acq_rel, or memory_order_seq_cst, and 
        the load is tagged with memory_order_consume, memory_order_acquire, or memory_order_seq_cst, and 
        each operation in the chain loads the value written by the previous operation, 
        then the chain of operations constitutes a release sequence and 
        the initial store synchronizes with (for memory_order_acquire or memory_order_seq_cst) or 
        is dependency-ordered-before (for memory_order_consume) the final load.
	
	Check Example Code

	If there are two threads reading, the second fetch_sub() will see the value written by the first and not the value written by the store.
	The first fetch_sub() does participate in the release sequence, and so the store() synchronizes with the second fetch_sub().
	
	There’s still no synchronizes-with relationship between the two consumer threads.

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::vector<int>    data_vec;
std::atomic_int     elem_cnt;

void fill_data() {
    const int    data_size = 10;
    data_vec.clear();

    for(int i = 0; i < data_size; ++i) {
        data_vec.push_back(i);
    }

    elem_cnt.store(data_size, std::memory_order_release);
}

void consume_data() {

    int index = elem_cnt.fetch_sub(1, std::memory_order_acquire);
    if(index <= 0) {
        std::cout << "Waiting for data ...\n";
        
    } else {
        std::cout << "Data element is " << data_vec[index-1] << '\n';
    }

}

int main() {
    std::thread wr_th(fill_data);
    std::vector<std::thread> rth_vec;
    for(int i = 0; i < 10; ++i) {
        rth_vec.push_back(std::thread(consume_data));
    }

    wr_th.join();
    for(auto & th : rth_vec) {
        th.join();
    }

    return 0;
}


/*****

If there’s one consumer thread, this is fine; fetch_sub() is a read with memory_order_acquire semantics, and 
the store had memory_order_release semantics, so
the store synchronizes with the load and the thread can read the item from the buffer.

If there are two threads reading, the second fetch_sub() will see 
the value written by the first and not the value written by the store.

Without the release sequence rule or memory_order_release on the fetch_sub operations, 
there would be nothing to require that the stores to the queue_data were visible to the second consumer, and
you would have a data race

There’s still no synchronizes-with relationship between the two consumer threads.

**********/


/*****
    END OF FILE
**********/


