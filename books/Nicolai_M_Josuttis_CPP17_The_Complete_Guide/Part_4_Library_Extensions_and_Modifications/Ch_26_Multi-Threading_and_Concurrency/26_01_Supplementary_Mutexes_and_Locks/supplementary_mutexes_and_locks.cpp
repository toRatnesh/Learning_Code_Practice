/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/thread/scoped_lock
	https://en.cppreference.com/w/cpp/thread/shared_mutex


Chapter 26 Multi-Threading and Concurrency

26.1 Supplementary Mutexes and Locks

26.1.1 std::scoped_lock

	-> to lock one or multiple mutexes. The mutexes may have different mutex types.
	-> if more than one mutex is passed, the constructor of scoped_lock uses  the variadic convenience function lock(...), 
		which guarantees that the call does not result in a deadlock
	-> the standard notes: “A deadlock avoidance algorithm such as try-and-back-off must be used, 
		but the specific algorithm is not specified to avoid over-constraining implementations”
	-> scoped_lock with a single constructor argument acts like a lock_guard).
		It then even defines the member mutex_type, which is not defined for multiple mutexes
	
26.1.2 std::shared_mutex

	-> Because on some platforms mutexes that don’t support timed locks can be implemented more efficient, now the type shared_mutex was introduced
	-> operations:
		• for exclusive locks: lock(), try_lock(), unlock()
		• for shared read-access: lock_shared(), try_lock_shared(), unlock_shared()
		• native_handle()
	
	Using a shared_mutex
		To have shared read-access (so that multiple readers do not block each other)
			use a shared_lock, which is a lock guard for shared read access
		for an exclusive write access
			use an exclusive lock guard, simple lock_guard or scoped_lock or a sophisticated unique_lock

*************/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>

std::vector<std::string>    svec;
std::vector<int>            ivec;

std::mutex                  svec_mutex;
std::mutex                  ivec_mutex;

std::shared_mutex           rwsv_mutex;

void producer(int num_elems) {
    /* pre C++17
        std::lock(svec_mutex, ivec_mutex);
        std::lock_guard<std::mutex> lg_svec_mutex(svec_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lg_ivec_mutex(ivec_mutex, std::adopt_lock);
    */
    std::scoped_lock    lg{svec_mutex, ivec_mutex};    
    for(int i = 0; i < num_elems; ++i) {
        svec.push_back("elem-"+std::to_string(i));
        ivec.push_back(i);
    }
    return;
}

void consumer() {
    std::scoped_lock    lg{svec_mutex, ivec_mutex};
    for(const auto & elem : svec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
    for(const auto & elem : ivec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';    
    return;
}

void writer(int num_elems) {  
    std::scoped_lock    lg{rwsv_mutex};     // exclusive lock
    ivec.clear();
    for(int i = 0; i < num_elems; ++i) {
        ivec.push_back(i);
    }
    return;
}

void reader(int id) {
    std::shared_lock    lg{rwsv_mutex};     // shared lock for read by mutiple threads
    std::cout << "reader-" << id << ": ";
    for(const auto & elem : ivec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';    
    return;
}

int main() {
    std::cout << "=== std::scoped_lock() ===\n";
{
    std::thread thr1{producer, 10};
    std::thread thr2{consumer};
    thr1.join();
    thr2.join();
}

{
    std::thread thr1{writer, 10};
    thr1.join();

    std::vector<std::thread>    thr_vec;
    for(int i = 0; i < 10; ++i) {
        thr_vec.push_back(std::thread(reader, i));
    }
    for(auto & th : thr_vec) {
        th.join();
    }
    
}

    return 0;
}

/**********
    END OF FILE
*************/


