/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/noexcept_spec
    https://en.cppreference.com/w/cpp/language/noexcept


Item 14: Declare functions noexcept if they won’t emit exceptions

C++98

	need to summarize the exception types a function might emit
	Changing an exception specification could break client code, because callers might be dependent on the original exception specification
	
C++11
	C++98-style exception specifications remain valid, but they’re deprecated
	unconditional noexcept is for functions that guarantee they won’t emit exceptions

noexcept optimization
	Failure to declare a function noexcept when you know that it won’t emit an exception is simply poor interface specification.

	Consider a function f that promises callers they’ll never receive an exception. The two ways of expressing that are:
		int f(int x) throw();	// no exceptions from f: C++98 style
		int f(int x) noexcept;	// no exceptions from f: C++11 style
	If, at runtime, an exception leaves f
	C++98, the call stack is unwound to f’s caller, and, after some actions not relevant here, program execution is terminated.
	C++11, runtime behavior is slightly different: the stack is only possibly unwound before program execution is terminated.
		
	In a noexcept function, optimizers need not keep the runtime stack in an unwindable state if an exception would propagate out of the function, 
	nor must they ensure that objects in a noexcept function are destroyed in the inverse order of construction should an exception leave the function.
	Functions with “throw()” exception specifications lack such optimization flexibility, as do functions with no exception specification at all.
		RetType function(params) noexcept;	// most optimizable
		RetType function(params) throw();	// less optimizable
		RetType function(params);			// less optimizable

Need for noexcept
	In C++11, many container functions replace calls to copy operations in C++98 
	with calls to move operations in C++11 only if the move operations are known to not emit exceptions. 
	The answer is obvious: it checks to see if the operation is declared noexcept.

	Exception-neutral functions are never noexcept, because they may emit such “just passing through” exceptions.
	Most functions, therefore, quite properly lack the noexcept designation.

Special implicit noexcept
	For some functions, being noexcept is so important, they’re that way by default.
	By default, all memory deallocation functions and all destructors—both user-defined and compilergenerated—are implicitly noexcept.
	There’s thus no need to declare them noexcept.

	The only time a destructor is not implicitly noexcept is when a data member of the class 
	(including inherited members and those contained inside other data members) 
	is of a type that expressly states that its destructor may emit exceptions (e.g., declares it “noexcept(false)”).
	Such destructors are uncommon.

wide contracts and narrow contracts
	A function with a wide contract has no preconditions. 
	Such a function may be called regardless of the state of the program, and it imposes no constraints on the arguments that callers pass it.
	Functions with wide contracts never exhibit undefined behavior.

	Functions without wide contracts have narrow contracts. For such functions, if a precondition is violated, results are undefined.

	library designers who distinguish wide from narrow contracts generally reserve noexcept for functions with wide contracts
	
Summary
	• noexcept is part of a function’s interface, and that means that callers may depend on it.
	• noexcept functions are more optimizable than non-noexcept functions.
	• noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
	• Most functions are exception-neutral rather than noexcept.

**********/

#include <iostream>
#include <exception>

void fun98() {
    std::cout << "Inside " << __func__ << ", throwing an exception\n";
    throw std::runtime_error("This is an exception from a function");
}

void funNoThrow98() throw() {
    std::cout << "Inside " << __func__ << " which is no throw, throwing an exception\n";
    throw std::runtime_error("This is an exception from a no throw function");
}

void fun11() {
    std::cout << "Inside " << __func__ << ", throwing an exception\n";
    throw std::runtime_error("This is an exception from a function");
}

void funNoThrow11() noexcept {
    std::cout << "Inside " << __func__ << " which is no throw, throwing an exception\n";

    // warning: 'throw' will always call 'terminate'
    throw std::runtime_error("This is an exception from a no throw function");
}

void use98Exception() {

    try {
        fun98();
    } catch (const std::exception & ex) {
        std::cout << "Caught exception: " << ex.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

    try {
        //funNoThrow98();   // RE error: terminate called after throwing an instance of 'std::runtime_error'
    } catch (const std::exception & ex) {
        std::cout << "Caught exception: " << ex.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

}

void use11Exception() {

    try {
        fun11();
    } catch (const std::exception & ex) {
        std::cout << "Caught exception: " << ex.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

    try {
        //funNoThrow11();   // RE error: terminate called after throwing an instance of 'std::runtime_error'
    } catch (const std::exception & ex) {
        std::cout << "Caught exception: " << ex.what() << '\n';
    } catch(...) {
        std::cout << "Unknown exception\n";
    }

}


int main() {

    use98Exception();

    use11Exception();

    return 0;
}

/*****
    END OF FILE
**********/


