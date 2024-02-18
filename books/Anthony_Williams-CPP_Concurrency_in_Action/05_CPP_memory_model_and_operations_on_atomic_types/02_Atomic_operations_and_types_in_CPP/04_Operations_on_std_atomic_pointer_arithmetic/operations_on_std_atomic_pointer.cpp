/*****

References
    Anthony Williams - C++ Concurrency in Action
5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.

5.2.4 Operations on std::atomic<T*>: pointer arithmetic

std::atomic<T*>
	atomic form of a pointer to some type T
	it can be both constructed and assigned from the suitable pointer values
	member functions load(), store(), exchange(), compare_exchange_weak(), and compare_exchange_strong()
	
new operations provided by std::atomic<T*> are the pointer arithmetic operations
	+=, -=, ++ and --,
		return the new value, return value is a plain T*
		always have memory_order_seq_cst semantics
		no way to specify memory-ordering semantics

	fetch_add() and fetch_sub(),
		return the original value, the return value is a plain T*
		also known as exchange-and-add
		allow the memory-ordering semantics to be specified
		atomic read-modify-write operation, so can have any of the memory-ordering tags and can participate in a release sequence

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

int iarr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

std::atomic<int *>  atm_intp{&iarr[0]};
int *   intp = &iarr[0];


void pointer_increment() {
    if(intp) {
        std::cout << *intp << '\n';
    }
    ++intp;
}

void atomic_pointer_increment() {
    if(atm_intp) {
        std::cout << *atm_intp << '\n';
    }
    ++atm_intp;
}

int main() {
    {
        std::cout << "=== Simple pointer ===\n";
        std::vector<std::thread> threads;
        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(pointer_increment));
        }
        for(auto & th : threads) {
            th.join();
        }
    }

    {
        std::cout << "=== Atomic pointer ===\n";
        std::vector<std::thread> threads;
        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(atomic_pointer_increment));
        }
        for(auto & th : threads) {
            th.join();
        }
    }

    {
        std::cout << "=== Some other operations on atomic pointer ===\n";
        std::atomic<int *>  atm_intp{&iarr[0]};
        if(atm_intp) {
            std::cout << "*atm_intp " << *atm_intp << '\n';
        }

        auto old_ptr = atm_intp.fetch_add(static_cast<std::ptrdiff_t>(2));
        if(old_ptr) {
            std::cout << "old_ptr is value obtained from fetch_add() member function, *old_ptr " << *old_ptr << '\n';
        }
        if(atm_intp) {
            std::cout << "*atm_intp " << *atm_intp << '\n';
        }

        old_ptr = atm_intp.fetch_add(static_cast<std::ptrdiff_t>(2));
        if(old_ptr) {
            std::cout << "old_ptr is value obtained from fetch_add() member function, *old_ptr " << *old_ptr << '\n';
        }
        if(atm_intp) {
            std::cout << "*atm_intp " << *atm_intp << '\n';
        }

        old_ptr = atm_intp.fetch_add(static_cast<std::ptrdiff_t>(5));
        if(old_ptr) {
            std::cout << "old_ptr is value obtained from fetch_add() member function, *old_ptr " << *old_ptr << '\n';
        }
        if(atm_intp) {
            std::cout << "*atm_intp " << *atm_intp << '\n';
        }


    }

    return 0;
}

/*****
    END OF FILE
**********/


