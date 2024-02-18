/*****

References
    Anthony Williams - C++ Concurrency in Action
    For C++20 changes visit https://en.cppreference.com/w/cpp/atomic/atomic_flag

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.

5.2.2 Operations on std::atomic_flag

std::atomic_flag
•	represents a Boolean flag
•	two states: set or clear
•	Objects of the std::atomic_flag type must be initialized to a clear state with ATOMIC_FLAG_INIT
•	the flag always starts clear
    std::atomic_flag f = ATOMIC_FLAG_INIT;

•	only atomic type to require such special treatment for initialization
•	guaranteed to be lock-free

after initialization, only three things you can do with it: 
1.	destroy it, 
2.	clear it, or 
3.	set it and query the previous value

clear() is a store operation and so can’t have memory_order_acquire or memory_order_acq_rel semantics
test_and_set() is a read-modify-write operation and so can have any of the memory-ordering
default for both is memory_order_seq_cst

std::atomic_flag ideally suited to use as a spinlock mutex
By its nature it does a busy-wait in lock()
it can’t even be used as a general Boolean flag, because it doesn’t have a simple non modifying query operation

class spinlock_mutex {
	std::atomic_flag flag;

   public:
	spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));
	}
	void unlock() { 
		flag.clear(std::memory_order_release); 
	}
};

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic_flag    ready_flg = ATOMIC_FLAG_INIT;
int     gval_lock = 0;
int     gval = 0;

void inc_without_lock() {
    ++gval;
    std::cout << gval << '\n';
}

void inc_with_lock() {
	while(ready_flg.test_and_set(std::memory_order_acquire)) { }
    ++gval_lock;
    std::cout << gval_lock << '\n';
	ready_flg.clear(std::memory_order_release);
}

int data = 0;
std::atomic_flag data_ready = ATOMIC_FLAG_INIT;
void producer() {
    data = 13;
    data_ready.test_and_set(std::memory_order_acquire);
    data_ready.notify_all();
}

void consumer() {
    data_ready.wait(false);
    std::cout << "Consumer thread " << std::this_thread::get_id() << ", data " << data << '\n';
}


int main() {
    {
        std::cout << "Without atomic \n";
        std::vector<std::thread> vec_thr;
        for(int cnt = 0; cnt < 10; ++cnt) {
            vec_thr.push_back(std::thread(inc_without_lock));
        }

        for(auto & thr : vec_thr) {
            thr.join();
        }
    }
    
    {
        std::cout << "With atomic \n";
        std::vector<std::thread> vec_thr;
        for(int cnt = 0; cnt < 10; ++cnt) {
            vec_thr.push_back(std::thread(inc_with_lock));
        }

        for(auto & thr : vec_thr) {
            thr.join();
        }
    }


    {
        std::cout << "Notify with atomic \n";
        std::vector<std::thread> vec_thr;
        vec_thr.push_back(std::thread(consumer));
        vec_thr.push_back(std::thread(consumer));
        vec_thr.push_back(std::thread(producer));
        for(auto & thr : vec_thr) {
            thr.join();
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/


