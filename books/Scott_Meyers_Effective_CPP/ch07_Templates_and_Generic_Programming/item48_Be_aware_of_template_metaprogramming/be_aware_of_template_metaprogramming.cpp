/*****

References
    Effective Modern C++ | Scott Meyers


Chapter 7: Templates and Generic Programming

    Generic programming — the ability to write code that is independent of the types of objects being manipulated

    It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
    that execute inside C++ compilers and that stop running when compilation is complete.

Item 48: Be aware of template metaprogramming
	Template metaprogramming (TMP) is the process of writing templatebased C++ programs that execute during compilation.
	
	strenghts:
	.	makes something easy that would be hard or impossible
	.	shift work from runtime to compile time

	using TMP executables can be efficient in terms of:
	.	smaller executable
	.	shorter runtime
	.	lesser memory requirements

	program using TMP takes longer time for compilation
	
	TMP has no real looping construct, so the effect of loops is accomplished via recursion.
	TMP loops don’t involve recursive function calls, they involve recursive template instantiations.
	
	accomplish:
	.	Ensuring dimensional unit correctness
	.	Optimizing matrix operations
	.	Generating custom design pattern implementations
	
	Summary:
		.	Template metaprogramming can shift work from runtime to compile-time, 
			thus enabling earlier error detection and higher runtime performance.
		.	TMP can be used to generate custom code based on combinations of policy choices, 
			and it can also be used to avoid generating code inappropriate for particular types.

**********/

#include <iostream>
#include <cstdint>


/*		C++ - 98 VERSION
template<unsigned N>
struct Factorial {
    static unsigned value;
};

template<unsigned N>
unsigned Factorial<N>::value = N * Factorial<N-1>::value;

template<>
struct Factorial<0> {
    static unsigned value;
};

unsigned Factorial<0>::value = 1;

*/


template<uint64_t N>
struct Factorial {
    static constexpr uint64_t value{N * Factorial<N-1>::value};
};

template<>
struct Factorial<0> {
    static constexpr uint64_t value{1};
};


int main() {
    std::cout << "Factorial<3>::value " << Factorial<3>::value << '\n';
	static_assert(6 == Factorial<3>::value, "Incorrect factorial vaue");
	std::cout << "Factorial<5>::value " << Factorial<5>::value << '\n';
    return 0;
}


/*****
    END OF FILE
**********/



