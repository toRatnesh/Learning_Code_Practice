/*****

References
    Anthony Williams - C++ Concurrency in Action

3.3 Alternative facilities for protecting shared data
	Apart from std::mutex there are other mechanism to protect shared data in special scenario. Like
	std::call_once
	std::shared_mutex
	std::recursive_mutex

3.3.2 Protecting rarely updated data structures
	In case where a shared data is updated rarely by a thread but accessed frequently by muttiple threads
	this update requires that the thread updating the data has exclusive access to the data until it has completed the operation
	after update data is again safe for multiple threads to access concurrently
	Using std::mutex in this case will eliminate the possible concurrency in reading the data structure when it isn’t undergoing modification

	reader-writer mutex
	It is used to solve problem with use of std::mutex in above case
	
	it allows for two different kinds of usage: 
	exclusive access by a single "writer" thread or shared, and concurrent access by multiple "reader" threads
	
	C++17 Standard Library provides two such mutexes
	
	std::shared_mutex			(since C++ 17)
	std::shared_timed_mutex		(since C++ 14)
	
		the performance is dependent on the number of processors involved and the relative workloads of the reader and updater threads
		
		To update,	use std::lock_guard<std::shared_mutex> and std::unique_lock<std::shared_mutex>, to obtain exclusive access
		To read,	use std::shared_lock<std::shared_mutex> to obtain shared access
		
		if any thread has a shared lock, a thread that tries to acquire an exclusive lock will block until all other threads have relinquished their locks
		if any thread has an exclusive lock, no other thread may acquire a shared or exclusive lock until the first thread has relinquished its lock
		
		std::shared_timed_mutex supports additional operations, so std::shared_mutex might offer a performance benefit on some platforms
		
**********/

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <string>

std::vector<std::string>    vec;
std::shared_mutex   rw_shared_mutex;

void writer(int num_elems) {
    std::scoped_lock    guard(rw_shared_mutex);
    for(int i = 0; i < num_elems; ++i) {
        vec.push_back("val-" + std::to_string(i));
    }
}

void reader(int thread_id) {
    std::shared_lock guard(rw_shared_mutex);
    std::cout << "Thread " << thread_id << '\n';
    for(auto & elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::thread thr1{writer, 10};
    thr1.join();

    std::vector<std::thread>    thr_vec;
    for(int i = 0; i < 10; ++i) {
        thr_vec.push_back(std::thread(reader, i));
    }
    for(auto & th : thr_vec) {
        th.join();
    }

    return 0;
}

/*****
    END OF FILE
**********/


