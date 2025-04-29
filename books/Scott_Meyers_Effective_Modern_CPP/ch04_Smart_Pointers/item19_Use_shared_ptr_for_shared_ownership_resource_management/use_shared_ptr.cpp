/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/memory/shared_ptr
    https://en.cppreference.com/w/cpp/memory/enable_shared_from_this

Item 19: Use std::shared_ptr for shared-ownership resource management

	An object accessed via std::shared_ptrs has its lifetime managed by those pointers through shared ownership.
	No specific std::shared_ptr owns the object.

	When the last std::shared_ptr pointing to an object stops pointing there 
	(e.g., because the std::shared_ptr is destroyed or made to point to a different object), 
	that std::shared_ptr destroys the object it points to.

	As with garbage collection, clients need not concern themselves with managing the lifetime of pointed-to objects, 
	but as with destructors, the timing of the objects’ destruction is deterministic.

reference count
	A std::shared_ptr can tell whether it’s the last one pointing to a resource by consulting the resource’s reference count, 
	a value associated with the resource that keeps track of how many std::shared_ptrs point to it. 
	std::shared_ptr constructors increment this count (usually—see below), 
	std::shared_ptr destructors decrement it, and 
	copy assignment operators do both (conditionally).

	If a std::shared_ptr sees a reference count of zero after performing a decrement, 
	no more std::shared_ptrs point to the resource, so the std::shared_ptr destroys it.

	The existence of the reference count has performance implications:
		• std::shared_ptrs are twice the size of a raw pointer
		• Memory for the reference count must be dynamically allocated
		• Increments and decrements of the reference count must be atomic

	move operation on std::shared_ptrs is therefore faster than copy operation: 
	copy operation requires incrementing the reference count, but move operation doesn’t

Deleter
	std::shared_ptr uses delete as its default
	Unlike unique_ptr, custom deleter is not part of the shared_ptr type
	
	two std::shared_ptr <Widget>s, each with a custom deleter of a different type
	could also be assigned to one another
	can be passed to a function taking a parameter of type std::shared_ptr<Widget>
	can be placed in a container of objects of that type
	
	None of these things can be done with std::unique_ptrs that differ in the types of their custom deleters

	specifying a custom deleter doesn’t change the size of a std::shared_ptr object
	
control block
	How can a std::shared_ptr refer to a deleter of arbitrary size without using any more memory?
	
	It may have to use more memory. However, that memory isn’t part of the std::shared_ptr object. 
	It’s on the heap or, if the creator of the std::shared_ptr took advantage of std::shared_ptr support for custom allocators, 
	it’s wherever the memory managed by the allocator is located.
		
	Earlier discussed the reference count is part of a larger data structure known as the control block
	There’s a control block for each object managed by std::shared_ptrs
	
	 _____________________			 _______________________
	|	Ptr to T      |-------------> 	|	T obj		|
	|		      |			 -----------------------
	|---------------------|				Control Block
	| Ptr to Control Block|			 _______________________
	|_____________________|-------------->	|			|
						|	Reference Count	|
						|-----------------------|
						|	Weak Count	|
						|-----------------------|
						|	Other data	|
						|-----------------------|
						|_______________________|
											
	An object’s control block is set up by the function creating the first std::shared_ptr to the object.
	
	following rules for control block creation are used:
	• std::make_shared (see Item 21) always creates a control block
	• A control block is created when a std::shared_ptr is constructed from a unique-ownership pointer
	• When a std::shared_ptr constructor is called with a raw pointer, it creates a control block

	A consequence of these rules is that constructing more than one std::shared_ptr from a single raw pointer 
	gives you a complimentary ride on the particle accelerator of undefined behavior, 
	because the pointed-to object will have multiple control blocks.
	
	code like this is bad:
	
	auto pw = new Widget;	// pw is raw ptr
	std::shared_ptr<Widget> spw1(pw, loggingDel);	// create control	block for *pw
	std::shared_ptr<Widget> spw2(pw, loggingDel);	// create 2nd control block for *pw!
	
	Suggestion:
		avoid passing raw pointers to a std::shared_ptr constructor
		
		if you must pass a raw pointer to a std::shared_ptr constructor, 
		pass the result of new directly instead of going through a raw pointer variable

std::enable_shared_from_this
	An especially surprising way that using raw pointer variables as std::shared_ptr constructor arguments 
	can lead to multiple control blocks involves the this pointer
	
	std::enable_shared_from_this is a template for a base class you inherit from 
	if you want a class managed by std::shared_ptrs to be able to safely create a std::shared_ptr from a this pointer
	
	std::enable_shared_from_this type parameter is always the name of the class being derived
	
	class Widget: public std::enable_shared_from_this<Widget> 	// Curiously Recurring Template Pattern (CRTP)
	{
		...
	};
	
	std::enable_shared_from_this defines a member function that creates a std::shared_ptr to the current object, 
	but it does it without duplicating control blocks.
	
	The member function is shared_from_this, and you use it in member functions whenever you want a std::shared_ptr that points to the same object as the this pointer.
	
	Internally, shared_from_this looks up the control block for the current object, 
	and it creates a new std::shared_ptr that refers to that control block. 
	The design relies on the current object having an associated control block. 
	For that to be the case, there must be an existing std::shared_ptr 
	(e.g., one outside the member function calling shared_from_this) that points to the current object. 
	If no such std::shared_ptr exists (i.e., if the current object has no associated control block), 
	behavior is undefined, although shared_from_this typically throws an exception.	

	To prevent clients from calling member functions that invoke shared_from_this before a std::shared_ptr points to the object, 
	classes inheriting from std::enable_shared_from_this often declare their constructors private and
	have clients create objects by calling factory functions that return std::shared_ptrs.

More Info	
	Under typical conditions, where the default deleter and default allocator are used 
	and where the std::shared_ptr is created by std::make_shared, 
	the control block is only about three words in size, and its allocation is essentially free
	
	In exchange for these rather modest costs, you get automatic lifetime management of dynamically allocated resources
	
	std::shared_ptr can’t work with arrays
	std::shared_ptr has an API that’s designed only for pointers to single objects
	
	--------------------------------------------------------
	NOTE:	SINCE C++17 std::shared_ptr SUPPORTS ARRAY
	--------------------------------------------------------
	
Summary

	• std::shared_ptrs offer convenience approaching that of garbage collection for the shared lifetime management of arbitrary resources.
	• Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, 
		incur overhead for control blocks, and require atomic reference count manipulations.
	• Default resource destruction is via delete, but custom deleters are supported. 
		The type of the deleter has no effect on the type of the std::shared_ptr.
	• Avoid creating std::shared_ptrs from variables of raw pointer type.
		
**********/

#include <iostream>
#include <memory>
#include <vector>

class St {
    int     val;
    public:
    
    ~St()   { std::cout << "~St()\n"; }
    St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    
    St(const St & other) : val(other.val) { 
        std::cout << "St(const St & other)\n"; 
    }
    St & operator=(const St & other) { 
        std::cout << "operator=(const St & other)\n"; 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::cout << "St(St && other)\n"; 
    }
    St & operator=(St && other) { 
        std::cout << "operator=(St && other)\n"; 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

    operator int() {
        return val;
    }
};

void deleteStFun(St * pst) {
    if(nullptr != pst) {
        std::cout << "Deleting St pointer inside deleteStFun\n";
        delete pst;
        pst = nullptr;
    }
}

class deleteFunctor {
    public:
    void operator()(St * pst) {
        if(nullptr != pst) {
            std::cout << "Deleting St pointer inside deleteStLambda\n";
            delete pst;
            pst = nullptr;
        }
    }
};

auto deleteStLambda = [](St * pst) {
    if(nullptr != pst) {
        std::cout << "Deleting St pointer inside deleteStLambda\n";
        delete pst;
        pst = nullptr;
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

class UsingThisForShared;
std::vector<std::shared_ptr<UsingThisForShared>>    uts_vec;

class UsingThisForShared : public std::enable_shared_from_this<UsingThisForShared> {

    St mst;

    UsingThisForShared(St && st) : mst(std::move(st)) {
        std::cout << "UsingThisForShared(St && st)\n";
    }


    public:
    ~UsingThisForShared() {
        std::cout << "~UsingThisForShared()\n";
    }

    UsingThisForShared(const UsingThisForShared & ) = delete;
    UsingThisForShared& operator=(const UsingThisForShared & ) = delete; 

    static std::shared_ptr<UsingThisForShared> create(St && st) {
        return std::shared_ptr<UsingThisForShared>(new UsingThisForShared(std::move(st)));
    }

    void insertInContainer() {
        uts_vec.push_back(shared_from_this());
    }

};

int main() {
    {   std::cout << "=== Using raw pointer ===\n";
        int * ip = new int{5};
        std::cout << "Deref pointer, value is " << *ip << '\n';
        delete ip; ip = nullptr;
    }

    {   std::cout << "=== Using shared pointer ===\n";
        std::shared_ptr<int> ip{ new int{5}};
        std::cout << "Deref pointer, value is " << *ip << '\n';
    }

    {   std::cout << "=== Using default deleter ===\n";
        std::shared_ptr<St> lp{ new St{3} };
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of shared pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Using lambda as custom deleter ===\n";
        std::shared_ptr<St> lp{ new St{3}, deleteStLambda};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of shared pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Using function pointer as custom deleter ===\n";
        std::shared_ptr<St> lp{ new St{3}, deleteStFun};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of shared pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Using functor as custom deleter ===\n";
        std::shared_ptr<St> lp{ new St{3}, deleteFunctor{}};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of shared pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Creating shared pointer from unique pointer ===\n";
        std::unique_ptr<St> lup{ new St{7}};
        std::shared_ptr<St> lsp1{std::move(lup)};
        std::shared_ptr<St> lsp2{lsp1};
        std::cout << "Number of shared pointer for this object " << lsp1.use_count() << '\n';
        std::shared_ptr<St> lsp3{std::move(lsp2)};
        std::cout << "Number of shared pointer for this object " << lsp3.use_count() << '\n';
    }

    {   std::cout << "=== Using factory ===\n";
        { auto lp = make_wheel(1); }
        { auto lp = make_wheel(2); }
        { auto lp = make_wheel(); }
    }

    {   std::cout << "=== Using shared pointer with different deleter inside a container ===\n";
        std::shared_ptr<St> lp1{ new St{5} };
        std::shared_ptr<St> lp2{ new St{6}, deleteStLambda};
        std::shared_ptr<St> lp3{ new St{7}, deleteStFun};

        std::vector<std::shared_ptr<St>>    sp_vec{lp1, lp2, lp3};
    }

    {   std::cout << "=== Bad Code: Multiple shared pointe using a single raw pointer ===\n";
        St * pst = new St{5};
        std::shared_ptr<St> lp1{pst};
        //std::shared_ptr<St> lp{pst};    // RE error: free(): double free detected in tcache 2
        
    }

    {   std::cout << "=== Using std::enable_shared_from_this to safely create shared pointer from this ===\n";
        std::shared_ptr<UsingThisForShared> luts1 = UsingThisForShared::create(St{11});        
        luts1->insertInContainer();

        std::shared_ptr<UsingThisForShared> luts2 = UsingThisForShared::create(St{13});        
        luts2->insertInContainer();

        std::cout << "No of entries in vector " << uts_vec.size() << '\n';
        std::cout << "uts_vec[0].use_count() " << uts_vec[0].use_count() << '\n';
        std::cout << "uts_vec[1].use_count() " << uts_vec[1].use_count() << '\n';
        std::cout << "std::vector<std::shared_ptr<UsingThisForShared>>  will go out of scope after main";
    }


    return 0;
}

/*****
    END OF FILE
**********/


