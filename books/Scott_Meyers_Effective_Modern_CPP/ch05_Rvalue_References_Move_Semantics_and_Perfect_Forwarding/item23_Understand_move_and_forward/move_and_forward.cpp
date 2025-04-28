/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/utility/move
    https://en.cppreference.com/w/cpp/utility/forward

	•	Move semantics makes it possible for compilers to replace expensive copying operations with less expensive moves.
	•	Perfect forwarding makes it possible to write function templates that take arbitrary arguments and 
		forward them to other functions such that the target functions receive exactly 
		the same arguments as were passed to the forwarding functions.

	Rvalue references are the glue that ties these two rather disparate features together. 
	They’re the underlying language mechanism that makes both move semantics and perfect forwarding possible.

	std::move doesn’t move anything, for example, and perfect forwarding is imperfect
	The construct “type&&” doesn’t always represent an rvalue reference.

	it’s especially important to bear in mind that a parameter is always an lvalue, 
	even if its type is an rvalue reference. That is, given
		void f(Widget&& w);
	the parameter w is an lvalue, even though its type is rvalue-reference-to-Widget

Item 23: Understand std::move and std::forward

	std::move doesn’t move anything. std::forward doesn’t forward anything. 
	At runtime, neither does anything at all. They generate no executable code. Not a single byte.

	std::move and std::forward are merely functions (actually function templates) that perform casts.
	std::move unconditionally casts its argument to an rvalue, while
	std::forward performs this cast only if a particular condition is fulfilled.


std::move
	sample implementation of std::move in C++11

	template<typename T> // in namespace std
	typename remove_reference<T>::type&&
	// decltype(auto) move(T&& param)						// C++14
	move(T&& param) {
		using ReturnType = typename remove_reference<T>::type&&;
		// using ReturnType = remove_reference_t<T>&&;		// C++14
		return static_cast<ReturnType>(param);
	}


	The “&&” part of the function’s return type implies that std::move returns an rvalue reference, 
	but, as Item 28 explains, if the type T happens to be an lvalue reference, T&& would become an lvalue reference. 
	To prevent this from happening, the type trait (see Item 9) std::remove_reference is applied to T, 
	thus ensuring that “&&” is applied to a type that isn’t a reference.
	
	In truth, rvalues are only usually candidates for moving.
	
	The rvalue can, however, be passed to the copy constructor, 
	because an lvalue-reference-to-const is permitted to bind to a const rvalue.
	
	Conclusion:
	First, don’t declare objects const if you want to be able to move from them. 
	Move requests on const objects are silently transformed into copy operations. 
	
	Second, std::move not only doesn’t actually move anything, 
	it doesn’t even guarantee that the object it’s casting will be eligible to be moved. 
	The only thing you know for sure about the result of applying std::move to an object is that it’s an rvalue.


std::forward
	std::forward conditionally casts its argument to an rvalue
	it casts to an rvalue only if its argument was initialized with an rvalue
	
	how can std::forward tell whether param was initialized with an lvalue or an rvalue?
	that information is encoded in logAndProcess’s template parameter T. 
	That parameter is passed to std::forward, which recovers the encoded information.
	For details on exactly how that works, consult Item 28.
	
std::move and std::forward
	std::move always casts, while std::forward only sometimes does
	std::forward can do it all what std::move does
	
	Of course, neither function is really necessary, because we could write casts everywhere, 
	but that would be, well, yucky.
	
	std::move’s attractions are convenience, reduced likelihood of error, and greater clarity
	
	In the example code below if we use std::forward instead of std::move
	that std::move requires only a function argument (rhs.s), while 
	std::forward requires both a function argument (rhs.s) and a template type argument(std::string)

	std::move requires less typing than std::forward, and 
	it spares us the trouble of passing a type argument that encodes that the argument we’re passing is an rvalue. 
	It also eliminates the possibility of our passing an incorrect type 
	(e.g., std::string&, which would result in the data member s being copy constructed instead of move constructed).

Summary
	•	std::move performs an unconditional cast to an rvalue. In and of itself, it doesn’t move anything.
	•	std::forward casts its argument to an rvalue only if that argument is bound to an rvalue.
	•	Neither std::move nor std::forward do anything at runtime.

**********/

#include <iostream>

class St {
    int     val;
    public:
    
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    explicit St(const int ival) : val(ival) { std::puts("St(const int ival)"); }
    
    St(const St & other) : val(other.val) { 
        std::puts("St(const St & other)"); 
    }
    St & operator=(const St & other) { 
        std::puts("operator=(const St & other)"); 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::puts("St(St && other)"); 
    }
    St & operator=(St && other) { 
        std::puts("operator=(St && other)"); 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};


void processSt(const St & ) {
    std::puts("processSt(const St & tval)");
}

void processSt(St && ) {
    std::puts("processSt(St && tval)");
}

template<typename T>
void processItWithoutForward(T && tval) {
    // But tval, like all function parameters, is an lvalue.
    // Every call to processSt inside processItWithoutForward will thus want to 
    // invoke the lvalue overload for process.
    processSt(tval);
}

template<typename T>
void processItWithForward(T && tval) {
    // std::forward is a conditional cast: it casts to an rvalue 
    // only if its argument was initialized with an rvalue
    processSt(std::forward<T>(tval));
}

int main() {

    {   std::puts("=== Understanding std::move ===");

        { std::puts("--- using move constructor ---");
            St st1; St st2{std::move(st1)}; }
            
        { std::puts("--- using move assignment ---");
            St st1; St st2; st2= std::move(st1); }

        std::puts("--- move constructor takes an rvalue reference to a non-const, so move requests on const objects are silently transformed into copy operations ---");
        { std::puts("--- using wrong move constructor fallback to copy construtor ---");
            const St st1; St st2{std::move(st1)}; }

        { std::puts("--- using wrong move assignment fallback to copy assignment ---");
            const St st1; St st2; st2= std::move(st1); }
    }

    {   std::puts("=== Understanding std::forward ===");

        {
            St st1;
            St st2;
            
            std::puts("--- Processing without std::forward ---");
            processItWithoutForward(st1);
            processItWithoutForward(std::move(st1));
            
            std::puts("--- Processing using std::forward ---");
            processItWithForward(st2);
            processItWithForward(std::move(st2));
        }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


