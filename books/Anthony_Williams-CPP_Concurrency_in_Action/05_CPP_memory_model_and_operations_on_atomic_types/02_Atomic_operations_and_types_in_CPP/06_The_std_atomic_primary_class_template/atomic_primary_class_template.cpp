/*****

References
    Anthony Williams - C++ Concurrency in Action

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.


5.2.6 The std::atomic<> primary class template

For a user-defined type UDT, std::atomic<UDT> provides the same interface as std::atomic<bool>
load(), store(), exchange(), compare_exchange_weak(), compare_exchange_strong()

the type must have a trivial copy assignment operator
the type must not have any virtual functions or virtual base classes and must use the compiler-generated copy-assignment operator 

Not only that, but every base class and non-static data member of a user-defined type must also have a trivial copy-assignment operator
This permits the compiler to use memcpy() or an equivalent operation for assignment operations
the compare-exchange operations do bitwise comparison as if using memcmp

If the type provides comparison operations that have different semantics, or the type has padding bits that do not participate in normal comparisons, then this can lead to a compare-exchange operation failing, even though the values compare equally.

If your UDT is the same size as (or smaller than) an int or a void*, most common platforms will be able to use atomic instructions for std::atomic<UDT>
platforms that support a so-called double-word-compare-and-swap (DWCAS) instruction corresponding to the compare_exchange_xxx functions will also be able to use atomic instructions for user-defined types that are twice the size of an int or void*

-------------------------------------------------------------------------------------------------------------------------
Operation			atomic_flag		atomic<bool>		atomic<T*>		atomic<integral-type>		atomic<othertype>
-------------------------------------------------------------------------------------------------------------------------
test_and_set			Y
clear					Y
is_lock_free 							Y					Y					Y							Y
load									Y					Y					Y							Y
store									Y					Y					Y							Y
exchange								Y					Y					Y							Y
compare_exchange_weak, 
compare_exchange_strong					Y					Y					Y							Y
fetch_add,	+=												Y					Y
fetch_sub,	-=												Y					Y
fetch_or,	|=																	Y
fetch_and,	&=																	Y
fetch_xor,	^=																	Y
++,	--														Y					Y
-------------------------------------------------------------------------------------------------------------------------

**********/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <string>

struct S1 {
    int     ival;
};

struct S2 {
    int             ival;
    std::string     sval;
};

class C1 {
    public:
    int     ival;
};

class C2 {
    public:
    int             ival;
    std::string     sval;
};

class C3 {
    int             ival;
    public:
    C3()    {}
    C3(int ival) : ival(ival) { }
    // for atomic can not have own copy and move operations
    // only compiler generated copy and move is allowed
    // C3(const C3 & other) : ival(other.ival) { }

    int get() {
        return ival;
    }
};

std::atomic<C3> atm_cval;
void producer(int val) {
    C3 c{val};
    atm_cval.store(c);
}

void consumer() {
    std::cout << "val is " << atm_cval.load().get() << '\n'; 
}

int main() {

    {
        std::cout << "=== struct with int ===\n";
        std::atomic<S1>     val;
        S1  s11{5};
        val.store(s11);
        S1 s= val.load();
        std::cout << s.ival << ' ' << val.load().ival << '\n';
        
        S1  s12{4};
        if(val.compare_exchange_strong(s11, s12)) {
            std::cout << "Value after exchange " << val.load().ival << '\n';
        }
    }

    {
        std::cout << "=== struct with int and std::string ===\n";
        //std::atomic<S2>     val;    // static assertion failed: std::atomic requires a trivially copyable type
    }

    {
        std::cout << "=== class with int ===\n";
        std::atomic<C1>     val;
        C1  c11{27};
        val.store(c11);
        C1 c= val.load();
        std::cout << c.ival << ' ' << val.load().ival << '\n';
        
        C1  c12{73};
        if(val.compare_exchange_strong(c11, c12)) {
            std::cout << "Value after exchange " << val.load().ival << '\n';
        }
    }

    {
        std::cout << "=== class with int and std::string ===\n";
        //std::atomic<C2>     val;    // static assertion failed: std::atomic requires a trivially copyable type
    }


    {
        std::cout << "=== class with int ===\n";
        std::atomic<C3>     val;
        C3  c31{13};
        val.store(c31);
        C3 c= val.load();
        std::cout << c.get() << ' ' << val.load().get() << '\n';
        
        C3  c32{56};
        if(val.compare_exchange_strong(c31, c32)) {
            std::cout << "Value after exchange " << val.load().get() << '\n';
        }
    }

    {
        std::vector<std::thread>    threads;

        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(producer, i));
        }

        for(int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(consumer));
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


