/*****

References
    Anthony Williams - C++ Concurrency in Action

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.


5.2.3 Operations on std::atomic<bool>

•	more fullfeatured Boolean flag
•	can construct it from a non-atomic bool, so it can be initially true or false
•	can also assign to instances of std::atomic<bool> from a non-atomic bool
std::atomic<bool> b(true);
b=false;

another common pattern with the atomic types: the assignment operators they support return values (of the corresponding non-atomic type) rather than references

store(),	to write
exchange(),to replace the stored value with a new one of your choosing and atomically retrieve the original value
		exchange() is a read-modify-write operation
load(),	to query of the value, also supports a plain nonmodifying implicit conversion to plain bool
std::atomic<bool> b;
bool x=b.load(std::memory_order_acquire);
b.store(true);
x=b.exchange(false,std::memory_order_acq_rel);

Storing A New Value (Or Not) Depending On The Current Value

compare_exchange_weak() and compare_exchange_strong()
compares the value of the atomic variable with a supplied expected value and if they’re
equal		stores the supplied desired value
not equal	the expected value is updated with the value of the atomic variable

return
true	if the store was performed and operation succeed
false	otherwise

For compare_exchange_weak(), the store might fail even if the original value was equal to the expected value
This is called a spurious failure, because the reason for the failure is a function of timing rather than the values of the variables

compare_exchange_strong() is guaranteed to return false only if the value wasn’t equal to the expected value

compare-exchange functions are also unusual in that they can take two memoryordering parameters
it might be desirable for a successful call to have memory_order_acq_rel semantics, whereas a failed call has memory_order_relaxed semantics

You also can’t supply stricter memory ordering for failure than for success
If you don’t specify an ordering for failure, it’s assumed to be the same as that for success, except that the release part of the ordering is stripped:

Following two calls to compare_exchange_weak() are equivalent:
	std::atomic<bool> b;
	bool expected;
	b.compare_exchange_weak(expected,true, memory_order_acq_rel,memory_order_acquire);
	b.compare_exchange_weak(expected,true,memory_order_acq_rel);

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic_bool    ready_flg = false;
int     gval_lock = 0;
int     gval = 0;

void inc_without_lock() {
    ++gval;
    std::cout << gval << '\n';
}

void inc_with_lock() {
	while(ready_flg.load(std::memory_order_acquire)) { }
    ready_flg.store(true, std::memory_order_release);
    ++gval_lock;
    std::cout << gval_lock << '\n';
	ready_flg.store(false, std::memory_order_release);
}

int data = 0;
std::atomic_bool data_ready = false;
void producer() {
    data = 13;
    data_ready.store(true);
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


