/*****

References
    Anthony Williams - C++ Concurrency in Action

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.

5.2.5 Operations on standard atomic integral types

set of operations load(), store(), exchange(), compare_exchange_weak(), and compare_exchange_strong()
comprehensive set of operations available: fetch_add(), fetch_sub(), fetch_and(), fetch_or(), fetch_xor()
ompound-assignment forms of these operations +=, -=, &=, |=, and ^=
pre- and post-increment and decrement ++x, x++, --x, and x--

only division, multiplication, and shift operators are missing
Because atomic integral values are typically used either as counters or as bitmasks
additional operations can easily be done using compare_exchange_weak() in a loop, if required

named functions atomically perform their operation and return the old value, whereas the compound-assignment operators return the new value

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

int                 ival{0};
std::atomic_int     atm_ival{0};

void increment() {
    ++ival;
}

void atomic_increment() {
    ++atm_ival;
}


std::atomic_int     data{5};

void producer() {
    data = 10;   
}

void consumer() {
    std::cout << "Data is " << data << '\n';
}

std::atomic_int     data2{5};

void producer_02() {
    data2.store(10);   
}

void consumer_02() {
    std::cout << "Data is " << data2.load() << '\n';
}

int main() {
    std::size_t thr_count = 10;

    {
        std::cout << "=== non atomic increment ===\n";
        std::vector<std::thread>   threads;
        for(std::size_t i = 0; i < thr_count; ++i) {
            threads.push_back(std::thread(increment));
        }

        for(auto & th : threads) {
            th.join();
        }

        std::cout << "ival " << ival << '\n';
    }

    {
        std::cout << "=== atomic increment ===\n";
        std::vector<std::thread>   threads;
        for(std::size_t i = 0; i < thr_count; ++i) {
            threads.push_back(std::thread(atomic_increment));
        }

        for(auto & th : threads) {
            th.join();
        }

        std::cout << "atm_ival " << atm_ival << '\n';
    }

    {
        std::cout << "=== assign and access ===\n";

        std::vector<std::thread>   threads;
        threads.push_back(std::thread(consumer));
        threads.push_back(std::thread(consumer));
        threads.push_back(std::thread(producer));

        for(auto & th : threads) {
            th.join();
        }        
    }

    {
        std::cout << "=== store and load ===\n";
        std::vector<std::thread>   threads;
        threads.push_back(std::thread(consumer_02));
        threads.push_back(std::thread(consumer_02));
        threads.push_back(std::thread(producer_02));
        
        for(auto & th : threads) {
            th.join();
        }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


