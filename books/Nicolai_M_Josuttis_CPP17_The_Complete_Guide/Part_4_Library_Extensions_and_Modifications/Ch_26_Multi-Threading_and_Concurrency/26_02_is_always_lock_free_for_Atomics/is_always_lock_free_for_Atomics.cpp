/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/atomic/atomic
	https://en.cppreference.com/w/cpp/atomic/atomic/is_always_lock_free
	https://en.cppreference.com/w/cpp/atomic/atomic_is_lock_free

Chapter 26 Multi-Threading and Concurrency

26.2 is_always_lock_free() for Atomics
	can now check with a C++ library feature whether a specific atomic type can always be used without locks
	If the value is true, then for any object of the corresponding atomic type is_lock_free() yields true
	if constexpr(atomic<T>::is_always_lock_free) {
		static_assert(atomic<T>().is_lock_free()); // never fails
	}
	reason to replace the macro by a static member is to have more type safety and support the use of this checks in tricky generic code (e.g., using SFINAE)

	std::atomic<> can also be used for trivially copyable types. 
	Thus, you can also check, whether your own structure would need locks if used atomically.

*************/

#include <iostream>
#include <vector>
#include <string>
#include <atomic>

struct Coll {
    int iarr[100];
};

struct Data {
    int  price;
    bool    available;
};


int main() {

    std::cout << "=== std::scoped_lock() ===\n";
    std::atomic<Coll>   at_coll;
    std::atomic<Data>   at_data;

    std::cout << std::boolalpha << "std::atomic_is_lock_free(&at_coll): " << std::atomic_is_lock_free(&at_coll) << '\n';
    std::cout << std::boolalpha << "std::atomic_is_lock_free(&at_data): " << std::atomic_is_lock_free(&at_data) << '\n';

    std::cout << std::boolalpha << "at_coll.is_lock_free(): " << at_coll.is_lock_free() << '\n';
    std::cout << std::boolalpha << "at_data.is_lock_free(): " << at_data.is_lock_free() << '\n';

    std::cout << std::boolalpha << "std::atomic<Coll>::is_always_lock_free: " << std::atomic<Coll>::is_always_lock_free << '\n';
    std::cout << std::boolalpha << "std::atomic<Data>::is_always_lock_free: " << std::atomic<Data>::is_always_lock_free << '\n';

    //static_assert(std::atomic<Coll>::is_always_lock_free);
    static_assert(std::atomic<Data>::is_always_lock_free);

    return 0;
}

/**********
    END OF FILE
*************/


