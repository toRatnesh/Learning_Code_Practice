/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/language/alignas
    https://en.cppreference.com/w/cpp/memory/new/align_val_t


28 new and delete with Over-Aligned Data

    over-aligned types(since C++11), having a bigger alignment than the default alignment

    struct alignas(32) MyType32 {
        int i;
        char c;
        std::string s[4];
    };

    dynamic/heap allocation of over-aligned data is not handled correctly in C++11 and C++14
    operator new for over-aligned types by default ignores the requested alignment, so that a type usually 63-bytes aligned might, for example, only be 8-bytes or 16-bytes aligned

    this issue has been solved in C++17, that new overloads with an alignment argument are provided

28.1 Using new with Alignments
    a new  expression now guarantees that the requested heap memory is aligned as requested

    MyType32 * ptr = new MyType32;
    without any value for initialization the object is default initialized, but (sub)objects of fundamental type have an undefined value

    MyType32 * ptr = new MyType32{};
    you better use list initialization with curly braces to ensure that the (sub)objects either have their default value or 0/false/nullptr

28.1.1 Distinct Dynamic/Heap Memory Arenas

    The request for aligned memory might result in a call to get the memory from a disjoint memory allocation mechanism. 
    For this reason, a request for aligned memory might require a specific corresponding request to deallocate the aligned data.

    However, other implementations of new and delete are allowed for platforms, 
    which leads to the requirement that different internal functions have to be used to deallocate default-aligned and overaligned data.

    In contrast to the C standard, the C++ standard respects this situation and therefore conceptionally assumes that there are two disjoint, non-interoperable memory arenas, one for default-aligned and one for over-aligned data.

        std::string* p1 = new std::string;	// using default-aligned memory operations
        MyType32* p2 = new MyType32;		// using over-aligned memory operations
        ...
        delete p1;				// using default-aligned memory operations
        delete p2;				// using over-aligned memory operations
        
28.1.2 Passing the Alignment with the new Expression
	A way to request a specific over-alignment for a specific call of new

	std::string* p = new(std::align_val_t{64}) std::string;	// 64-bytes aligned
	MyType32* p = new(std::align_val_t{64}) MyType32{};		// 64-bytes aligned

	The type std::align_val_t is defined in header <new> as follows:

	namespace std {
		enum class align_val_t : size_t {
		};
	}

	It is provided to be able now to pass alignment requests to the corresponding implementation of operator new()
	When specifying the alignment with the new expression the compiler can’t use the type to know whether and which alignment was requested. The programmer has to specify which delete to call
	Unfortunately, there is no delete operator, where you can pass an additional argument, you have to call the corresponding operator delete() directly, which means that you have to know, which of the multiple overloads are implemented


	new() can be implemented in different ways in C++:
	• As a global function (different overloads are provided by default, which can be replaced by the programmer).
	• As type-specific implementations, which can be provided by the programmer and have higher priority than the global overloads.

	You can’t use a typedef or using declaration instead:
	using MyType64 = alignas(64) MyType32; // ERROR
	typedef alignas(64) MyType32 MyType64; // ERROR

	The reason is that a typedef or using declaration is only a new name/alias for the original type and what is requested here is a different type following different rules for alignment.

	// Use this to get nullptr as a return value instead of throwing std::bad_alloc
	std::string* p = new(std::align_val_t{64}, std::nothrow) std::string;

*************/

#include <iostream>

struct alignas(8) MyType32 {
    int     idata;
    float   fdata;
    char    cdata;
};

int main() {
    {
        MyType32 * ptr = new MyType32;
        if(ptr) std::cout << "new MyType32 is default initilalized subobjects have undefined value\n";
        std::cout << ptr->idata << ' ' << ptr->fdata << ' ' << ptr->cdata << '\n';
        delete ptr; ptr= nullptr;
    }

    {
        MyType32 * ptr = new MyType32{};
        if(ptr) std::cout << "new MyType32 is default initilalized subobjects have default value\n";
        std::cout << ptr->idata << ' ' << ptr->fdata << ' ' << ptr->cdata << '\n';
        delete ptr; ptr= nullptr;
    }

    {
        MyType32 * ptr = new(std::align_val_t{4}) MyType32{5, 5.6f, 'A'};
        std::cout << ptr->idata << ' ' << ptr->fdata << ' ' << ptr->cdata << '\n';
        delete ptr; ptr= nullptr;
    }

    {
        MyType32 * ptr = new(std::align_val_t{16}) MyType32{5, 5.6f, 'A'};
        std::cout << ptr->idata << ' ' << ptr->fdata << ' ' << ptr->cdata << '\n';
        delete ptr; ptr= nullptr;
    }

    return 0;
}

/**********
    END OF FILE
*************/


