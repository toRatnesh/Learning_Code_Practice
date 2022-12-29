/************

References
    C++17 - The Complete Guide | Nicolai M. Josuttis

9. Class Template Argument Deduction (CTAD)

    Since C++17, you do not need to specify the template arguments explicitly, if the constructor is able to deduce all template parameters using CTAD.
    std::complex c{5.1,3.3};			// OK: std::complex<double> deduced
    std::vector v2 {"hello", "world"};	// OK: std::vector<const char*> deduced

9.2 Deduction Guides
	We use deduction guides to provide additional CTAD or fix existing deductions defined by constructors
	The deduction guide only matters for the deduction of the template types. It is irrelevant for the actual constructor call after the types are deduced

	NOTE: Decay means that raw arrays convert to pointers and top-level qualifiers, such as const and references, are ignored

9.2.5 Deduction Guides for Aggregates
	Deduction guides can be used in generic aggregates to enable CTAD
	However, as usual for aggregates, you still need curly braces. Otherwise, type T is successfully deduced, but the initialization is an error

*************/

#include <iostream>
#include <string>

template<typename T>
struct AggregateWithDeduction {
    T val;
};
AggregateWithDeduction(char const *) -> AggregateWithDeduction<std::string>;

template<typename T>
struct AggregateWithExplicitDeduction {
    T val;
};
explicit AggregateWithExplicitDeduction(char const *) -> AggregateWithExplicitDeduction<std::string>;

int main() {

    {
        std::clog << "=== Deduction Guides for Aggregates\n";

        AggregateWithDeduction          awd1{"Aggregate with explciit decution"};
        AggregateWithExplicitDeduction  awed1{"Aggregate with explciit decution"};

        //AggregateWithDeduction            awd2("Aggregate with explciit decution"); // error: no matching function for call to 'AggregateWithDeduction<std::__cxx11::basic_string<char> >::AggregateWithDeduction(const char [33])'
        //AggregateWithExplicitDeduction    awed2("Aggregate with explciit decution");     // error: no matching function for call to 'AggregateWithExplicitDeduction<std::__cxx11::basic_string<char> >::AggregateWithExplicitDeduction(const char [33])'
        
        //AggregateWithDeduction            awd3 = "Aggregate with explciit decution"; // error: conversion from 'const char [33]' to non-scalar type 'AggregateWithDeduction<std::__cxx11::basic_string<char> >' requested
        //AggregateWithExplicitDeduction    awed3 = "Aggregate with explciit decution";    // error: class template argument deduction failed:
        
        AggregateWithDeduction              awd4 = {"Aggregate with explciit decution"};
        //AggregateWithExplicitDeduction    awed4 = {"Aggregate with explciit decution"};  // error: class template argument deduction for 'AggregateWithExplicitDeduction<T>' failed: explicit deduction guide selected in copy-list-initialization
        
        AggregateWithDeduction              awd5 = AggregateWithDeduction{"Aggregate with explciit decution"};
        AggregateWithExplicitDeduction      awed5 = AggregateWithExplicitDeduction{"Aggregate with explciit decution"};
    }

	return 0;
}

/*******
    END OF FILE
*********/


