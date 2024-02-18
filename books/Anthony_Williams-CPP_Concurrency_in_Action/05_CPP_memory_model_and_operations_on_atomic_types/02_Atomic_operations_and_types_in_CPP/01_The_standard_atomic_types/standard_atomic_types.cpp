/*****

References
    Anthony Williams - C++ Concurrency in Action
    https://en.cppreference.com/w/cpp/atomic/atomic
    https://en.cppreference.com/w/cpp/header/atomic
    https://en.cppreference.com/w/cpp/atomic/memory_order

5.2 Atomic operations and types in C++

An atomic operation is an indivisible operation. It’s either done or not done.
If the non-atomic operation is composed of atomic operations (for example, assignment to a struct with atomic members), you might observe or end up with a value that is a mixed-up combination of the various values stored.

5.2.1 The standard atomic types

All operations on atomic types are atomic, and only operations on these types are atomic in the sense of the language definition.
For an atomic type is_always_lock_free member function
	returns true, if operations on a given type are done directly with atomic instructions
	returns false, if operations on a given type are done using a lock internal to the compiler and library
	
The library provides a set of macros to identify at compile time whether the atomic types for the various integral types are lock-free.
Since C++17, all atomic types have a static constexpr member variable, X::is_always_lock_free
ATOMIC_BOOL_LOCK_FREE, 
ATOMIC_CHAR_LOCK_FREE,ATOMIC_CHAR16_T_LOCK_FREE, ATOMIC_CHAR32_T_LOCK_FREE, ATOMIC_WCHAR_T_LOCK_FREE,
ATOMIC_SHORT_LOCK_FREE,ATOMIC_INT_LOCK_FREE, ATOMIC_LONG_LOCK_FREE, ATOMIC_LLONG_LOCK_FREE, 
and ATOMIC_POINTER_LOCK_FREE

evaluate to the value 
•	0 if the atomic type is never lock-free
•	1 if the lock-free status of the corresponding atomic type is a runtime property
•	2 if the atomic type is always lock-free

std::atomic_flag is a simple Boolean flag, and operations on this type are required to be lock-free
std::atomic<> class templates are a bit more full-featured but may not be lockfree
You can use the set of names, to refer to the implementation-supplied atomic types
C++17, these are always aliases for the corresponding std::atomic<> specializations

The standard atomic types are not copyable or assignable in the conventional sense

std::atomic<> can be used to create an atomic variant of a user defined type.
Because it’s a generic class template, the operations are limited to load(), store() (and assignment from and conversion to the user-defined type), exchange(), compare_exchange_weak(), and compare_exchange_strong().
Each of the operations on the atomic types has an optional memory-ordering argument which is one of the values of the std::memory_order enumeration.

The operations are divided into three categories:
1.	Store operations, which can have memory_order_relaxed, memory_order_release, or memory_order_seq_cst ordering
2.	Load operations, which can have memory_order_relaxed, memory_order_consume, memory_order_acquire, or memory_order_seq_cst ordering
3.	Read-modify-write operations, which can have memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_release, memory_order_acq_rel, or memory_order_seq_cst ordering

**********/

#include <iostream>
#include <atomic>
#include <string>

enum class Color {
    RED,
    BLACK,
    WHITE
};

class EmpptyC {

};

struct S {
    int m;
};

class C {
    int m;
public:
    void set(int m) { m = m; }
    int get() { return m; }
};

class Cs {
    int         mi;
    std::string ms;
public:
    void set(int mi) { mi = mi; }
    int get() { return mi; }
};

int main() {

    std::cout << std::boolalpha <<
    
    // CE error: 'is_always_lock_free' is not a member of 'std::atomic_flag'
    //"std::atomic_flag::is_always_lock_free    "       << std::atomic_flag::is_always_lock_free << '\n' <<

    "std::atomic_bool::is_always_lock_free      "       << std::atomic_bool::is_always_lock_free << '\n' <<
    "std::atomic_char::is_always_lock_free      "       << std::atomic_char::is_always_lock_free << '\n' <<
    "std::atomic_int::is_always_lock_free       "       << std::atomic_int::is_always_lock_free << '\n' <<
    "std::atomic_intptr_t::is_always_lock_free  "       << std::atomic_intptr_t::is_always_lock_free << '\n' <<
    "std::atomic_size_t::is_always_lock_free    "       << std::atomic_size_t::is_always_lock_free << '\n' <<
    "std::atomic<Color>::is_always_lock_free    "       << std::atomic<Color>::is_always_lock_free << '\n' <<
    "std::atomic<EmpptyC>::is_always_lock_free  "       << std::atomic<EmpptyC>::is_always_lock_free << '\n' <<
    "std::atomic<S>::is_always_lock_free        "       << std::atomic<S>::is_always_lock_free << '\n' <<

    // CE error: static assertion failed: std::atomic requires a trivially copyable type
    //"std::atomic<Cs>::is_always_lock_free     "       << std::atomic<Cs>::is_always_lock_free << '\n' <<

    "std::atomic<C>::is_always_lock_free        "       << std::atomic<C>::is_always_lock_free << '\n';

    std::cout << '\n';



	std::atomic_flag	aflag;
	std::atomic_bool	ab;
	std::atomic_char	ac;
	std::atomic_int		ai;
	std::atomic_intptr_t	aip;
	std::atomic_size_t		asize;
	std::atomic<Color>		aenum_color;
	std::atomic<EmpptyC>	aempty_c;
	std::atomic<S>		ast;

    // CE error: static assertion failed: std::atomic requires a trivially copyable type
	//std::atomic<Cs>		at_cls_str;
    
	std::atomic<C>		at_cls;
	


    std::cout << std::boolalpha <<
    
    // CE error: 'struct std::atomic_flag' has no member named 'is_lock_free'    
    //"aflag.is_lock_free()    "       << aflag.is_lock_free() << '\n' <<

    "ab.is_lock_free()      "       << ab.is_lock_free() << '\n' <<
    "ac.is_lock_free()      "       << ac.is_lock_free() << '\n' <<
    "ai.is_lock_free()      "       << ai.is_lock_free() << '\n' <<
    "aip.is_lock_free()     "       << aip.is_lock_free() << '\n' <<
    "asize.is_lock_free()   "       << asize.is_lock_free() << '\n' <<
    "aenum_color.is_lock_free() "       << aenum_color.is_lock_free() << '\n' <<
    "aempty_c.is_lock_free()    "       << aempty_c.is_lock_free() << '\n' <<
    "ast.is_lock_free()     "       << ast.is_lock_free() << '\n' <<

    // CE error: static assertion failed: std::atomic requires a trivially copyable type
    //"at_cls_str.is_lock_free()    "       << at_cls_str.is_lock_free() << '\n' <<

    "at_cls.is_lock_free()  "       << at_cls.is_lock_free() << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


