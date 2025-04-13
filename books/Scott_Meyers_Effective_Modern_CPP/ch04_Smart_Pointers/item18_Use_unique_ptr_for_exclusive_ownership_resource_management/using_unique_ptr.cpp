/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/memory/unique_ptr

Item 18: Use std::unique_ptr for exclusive-ownership resource management

	by default, std::unique_ptrs are the same size as raw pointers, 
	and for most operations (including dereferencing), they execute exactly the same instructions.

	std::unique_ptr embodies exclusive ownership semantics. 
	A non-null std::unique_ptr always owns what it points to. 
	Moving a std::unique_ptr transfers ownership from the source pointer to the destination pointer. (The source pointer is set to null.)
	std::unique_ptr is thus a move-only type.
	Upon destruction, a non-null std::unique_ptr destroys its resource.

Deleter
	By default, that destruction would take place via delete, 
	but, during construction, std::unique_ptr objects can be configured to use custom deleters: 
	arbitrary functions (or function objects, including those arising from lambda expressions) 
	to be invoked when it’s time for their resources to be destroyed.

	All custom deletion functions accept a raw pointer to the object to be destroyed,

Size in case of deleter
	when using the default deleter std::unique_ptr objects may no longer be the same size as raw pointers
	function pointers generally cause the size of a std::unique_ptr to grow from one word to two
	function objects, the change in size depends on how much state is stored in the function object
	Stateless function objects (e.g., from lambda expressions with no captures) incur no size penalty

	If you find that a custom deleter makes your std::unique_ptrs unacceptably large, you probably need to change your design.

	std::unique_ptrs are even more popular as a mechanism for implementing the Pimpl Idiom.

Variants
	std::unique_ptr comes in two forms,
	1.	for individual objects (std::unique_ptr<T>)
	2.	for arrays (std::unique_ptr<T[]>)
	there’s no indexing operator (operator[]) for the single-object form, while the array form lacks dereferencing operators (operator* and operator->).

shared pointer using unique pointer
	std::unique_ptr easily and efficiently converts to a std::shared_ptr

Summary
• std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive-ownership semantics.
• By default, resource destruction takes place via delete, but custom deleters can be specified. Stateful deleters and function pointers as deleters increase the size of std::unique_ptr objects.
• Converting a std::unique_ptr to a std::shared_ptr is easy.

**********/

#include <iostream>
#include <memory>

class St {
    int     val;
    public:
    St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    ~St()   { std::cout << "~St()\n"; }
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
    std::unique_ptr<Wheel> lp{nullptr};
    if(1== val) {
        lp.reset(new AlloyWheel{});
    }
    else if(2 == val) {
        lp.reset(new SteelWheel{});
    }
    return lp;
}

int main() {
    {   std::cout << "=== Using raw pointer ===\n";
        int * ip = new int{5};
        std::cout << "Deref pointer, value is " << *ip << '\n';
        delete ip; ip = nullptr;
    }

    {   std::cout << "=== Using unique pointer ===\n";
        std::unique_ptr<int> ip{ new int{5}};
        std::cout << "Deref pointer, value is " << *ip << '\n';
    }

    {   std::cout << "=== Using default deleter ===\n";
        std::unique_ptr<St> lp{ new St{3} };
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of unique pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Using lambda as custom deleter ===\n";
        std::unique_ptr<St, decltype(deleteStLambda)> lp{ new St{3}, deleteStLambda};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of unique pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Using function pointer as custom deleter ===\n";
        std::unique_ptr<St, void(*)(St *)> lp{ new St{3}, deleteStFun};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of unique pointer is " << sizeof(lp) << '\n';
    }
    
    {   std::cout << "=== Using functor as custom deleter ===\n";
        std::unique_ptr<St, deleteFunctor> lp{ new St{3}, deleteFunctor{}};
        std::cout << "Deref pointer, value is " << *lp << '\n';

        std::cout << "Size of unique pointer is " << sizeof(lp) << '\n';
    }

    {   std::cout << "=== Creating shared pointer from unique pointer ===\n";
        std::unique_ptr<St> lup{ new St{7}};
        std::shared_ptr<St> lsp1{std::move(lup)};
        std::shared_ptr<St> lsp2{lsp1};
    }

    {   std::cout << "=== Using factory ===\n";
        { auto lp = make_wheel(1); }
        { auto lp = make_wheel(2); }
        { auto lp = make_wheel(); }
    }

    return 0;
}

/*****
    END OF FILE
**********/


