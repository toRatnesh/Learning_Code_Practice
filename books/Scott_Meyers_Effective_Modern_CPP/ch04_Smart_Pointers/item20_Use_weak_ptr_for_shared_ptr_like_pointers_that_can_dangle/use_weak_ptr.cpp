/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/memory/weak_ptr
    https://en.cppreference.com/w/cpp/memory/shared_ptr

Item 20: Use std::weak_ptr for std::shared_ptr like pointers that can dangle

	a smart pointer that acts like a std::shared_ptr (see Item 19), 
	but that doesn’t participate in the shared ownership of the pointed-to resource

	a pointer like std::shared_ptr that doesn’t affect an object’s reference count

	std::weak_ptr would deal with the possibility that what it points to has been destroyed

	std::weak_ptrs can’t be dereferenced, nor can they be tested for nullness

	std::weak_ptrs are typically created from std::shared_ptrs. 
	They point to the same place as the std::shared_ptrs initializing them, 
	but they don’t affect the reference count of the object they point to

	Even if there were dereferencing operations, separating the check and the dereference would
	introduce a race condition: between the call to expired and the dereferencing action

creating shared_ptr from the weak_ptr
	What you need is an atomic operation that checks to see if the std::weak_ptr has expired and, 
	if not, gives access to the object it points to. This is done by creating a std::shared_ptr from the std::weak_ptr.

	1. std::weak_ptr::lock
		std::weak_ptr::lock, which returns a std::shared_ptr. The std::shared_ptr is null if the std::weak_ptr has expired:

	2. std::shared_ptr constructor taking a std::weak_ptr as an argument
		In this case, if the std::weak_ptr has expired, an exception is thrown
		

Uses
	1.	Caching		See example
	2.	Observer	
	3.	shared_ptr cycles
		consider a data structure with objects A, B, and C in it, 
		where A and C share ownership of B and therefore hold std::shared_ptrs to it
				std::shared_ptr					std::shared_ptr
			A	------------------>		B	<------------------- C
			
		Suppose it’d be useful to also have a pointer from B back to A. What kind of pointer should this be?
				std::shared_ptr					std::shared_ptr
			A	------------------>		B	<------------------- C
				<------------------	
					pointer type?
					
		There are three choices:
		•	A raw pointer. With this approach, if A is destroyed, but C continues to point to B, 
			B will contain a pointer to A that will dangle. 
			B won’t be able to detect that, so B may inadvertently dereference the dangling pointer. 
			That would yield undefined behavior.
		•	A std::shared_ptr. In this design, A and B contain std::shared_ptrs to each other. 
			The resulting std::shared_ptr cycle (A points to B and B points to A) will prevent 
			both A and B from being destroyed.
			
		•	A std::weak_ptr. This avoids both problems above. If A is destroyed, B’s pointer back to it will dangle, 
			but B will be able to detect that. Furthermore, though A and B will point to one another, 
			B’s pointer won’t affect A’s reference count, 
			hence can’t keep A from being destroyed when std::shared_ptrs no longer point to it.			

weak_ptr and shared_ptr
	From an efficiency perspective, the std::weak_ptr story is essentially the same as that for std::shared_ptr.
	std::weak_ptr objects are the same size as std::shared_ptr objects
	weak_ptr make use of the same control blocks as std::shared_ptrs (see Item 19), and 
	operations such as construction, destruction, and assignment involve atomic reference count manipulations
	
	std::weak_ptrs don’t participate in the shared ownership of objects and 
	hence don’t affect the pointed-to object’s reference count
	
	There’s actually a second reference count in the control block, 
	and it’s this second reference count that std::weak_ptrs manipulate

    ------------------------------------------------------------------------------------------------
    // Reference - Item 21: Prefer std::make_unique and std::make_shared to direct use of new
    The control block contains a second reference count, one that tallies how many std::weak_ptrs refer to the control block.
    This second reference count is known as the weak count. When a std::weak_ptr checks to see if it has expired (see Item 19), 
    it does so by examining the reference count (not the weak count) in the control block that it refers to. 
    If the reference count is zero (i.e., if the pointed-to object has no std::shared_ptrs referring to it and has thus been destroyed), 
    the std::weak_ptr has expired. Otherwise, it hasn’t.

    As long as std::weak_ptrs refer to a control block (i.e., the weak count is greater than zero), 
    that control block must continue to exist. 
    And as long as a control block exists, the memory containing it must remain allocated. 
    The memory allocated by a std::shared_ptr make function, then, can’t be deallocated until 
    the last std::shared_ptr and the last std::weak_ptr referring to it have been destroyed.

    ------------------------------------------------------------------------------------------------

Summary
	• Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
	• Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
	
**********/

#include <iostream>
#include <memory>
#include <vector>

#define LOGEXP(...) std::cout << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n'

class St {
    int     val;
    public:
    explicit St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    ~St()   { std::cout << "~St()\n"; }
    operator int() {
        return val;
    }
};

class Wheel {
    public:
    virtual ~Wheel() { std::cout << "~Wheel()\n"; }
};

class AlloyWheel : public Wheel {
    public:
    ~AlloyWheel() { std::cout << "~AlloyWheel()\n"; }
};

class SteelWheel : public Wheel {
    public:
    ~SteelWheel() { std::cout << "~SteelWheel()\n"; }
};

auto make_wheel(const int val = 0) {
    std::shared_ptr<Wheel> lp{nullptr};
    if(1== val) {
        lp.reset(new AlloyWheel{});
    }
    else if(2 == val) {
        lp.reset(new SteelWheel{});
    }
    return lp;
}

struct Data {
    std::string data;
    //std::shared_ptr<Data> ptr;
    std::weak_ptr<Data> ptr;
    
    Data(const std::string str, std::shared_ptr<Data> ptr) : data(str), ptr(ptr) { 
        std::cout << "Data(const std::string st, std::shared_ptr<Data> ptr)\n"; 
    }
    ~Data()   { std::cout << "~Data()\n"; }   
};

int main() {

    {   std::cout << "=== Making weak_ptr from shared_ptr ===\n";
        std::shared_ptr<St> lsp{new St{7}};
        std::weak_ptr<St>   lwp{lsp};
        LOGEXP(lwp.use_count());
        LOGEXP(lsp.use_count());

        if(lwp.expired()) {
            std::cout << "Weak pointer has expired\n";
        } else {
            std::shared_ptr<St> lsp{lwp};
            LOGEXP(lwp.use_count());
            LOGEXP(lsp.use_count());            
        }

        if(lwp.expired()) {
            std::cout << "Weak pointer has expired\n";
        } else {
            std::shared_ptr<St> lsp = lwp.lock();
            LOGEXP(lwp.use_count());
            LOGEXP(lsp.use_count());            
        }

        lsp.reset();
        LOGEXP(lwp.use_count());
        LOGEXP(lsp.use_count());
        if(lwp.expired()) {
            std::cout << "Weak pointer has expired\n";
        } else {
            std::shared_ptr<St> lsp{lwp};
            LOGEXP(lwp.use_count());
            LOGEXP(lsp.use_count());            
        }        
    }

    {   std::cout << "=== Circular problem using shared_ptr ===\n";
        
        
        std::shared_ptr<Data>   b{new Data{"Data-B", nullptr}};
        std::shared_ptr<Data>   a{b};

        LOGEXP(a.use_count());
        LOGEXP(b.use_count());    
        
        {
            std::shared_ptr<Data>   c{b};
            
            LOGEXP(a.use_count());
            LOGEXP(b.use_count());
            LOGEXP(c.use_count());
            
        }
        b->ptr = a;
        
        LOGEXP(a.use_count());
        LOGEXP(b.use_count());
    }

    return 0;
}

/*****
    END OF FILE
**********/


