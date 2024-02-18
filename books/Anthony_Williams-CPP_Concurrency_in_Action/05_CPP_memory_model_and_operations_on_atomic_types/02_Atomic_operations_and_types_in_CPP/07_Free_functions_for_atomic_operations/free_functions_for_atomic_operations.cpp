/*****

References
    Anthony Williams - C++ Concurrency in Action

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.


5.2.7 Free functions for atomic operations

the nonmember functions are named after the corresponding member functions but with an atomic_ prefix
These functions are then overloaded for each of the atomic types

they come in two varieties:
	one without the tag and 
	one with an _explicit suffix and an additional parameter(s) for the memory-ordering tag(s)

	std::atomic_store(&atomic_var, new_value) 
	std::atomic_store_explicit(&atomic_var, new_value, std::memory_order_release)
	
all the free functions take a pointer to the atomic object as the first parameter
The free functions are designed to be C-compatible, so they use pointers rather than references in all cases

The operations on std::atomic_flag buck the trend in that they spell out the flag part in the names

*****
	The C++ Standard Library also provides free functions for accessing instances of std::shared_ptr<> in an atomic fashion
	The Concurrency TS also provides std::experimental::atomic_shared_ptr<T>, which is an atomic type
*****

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <memory>

std::atomic<std::shared_ptr<int>>    pdata{nullptr};

void producer() {
    auto temp = std::make_shared<int>(23);
    pdata.store(temp);
    pdata.notify_all();
}

void consumer() {
    pdata.wait(nullptr);
    auto temp = pdata.load();
    if(temp) {
        std::cout << "data is " << *temp << '\n';
    }
}

std::atomic_int     ival;

void producer_02(int i) {
    std::atomic_store(&ival, i);
}

void consumer_02() {
    std::cout << "val is " << std::atomic_load(&ival) << '\n';
}

int main() {
    {
        std::vector<std::thread>    threads;
        threads.push_back(std::thread(producer));
        threads.push_back(std::thread(consumer));
        threads.push_back(std::thread(consumer));

        for(auto & th : threads) {
            th.join();
        }        
    }

    {
        std::vector<std::thread>    threads;

        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(producer_02, i));
        }
        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(consumer_02));
        }        
        for(auto & th : threads) {
            th.join();
        }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


