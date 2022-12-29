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

9.2.2 Non-Template Deduction Guides
	Deduction guides don’t have to be templates and don’t have to apply to constructors

*************/

#include <iostream>
#include <string>

template<typename T>
struct StrWithoutDeduction {
    T val;
};

template<typename T>
struct StrWithDeductionGuide {
    T val;
};
StrWithDeductionGuide(char const *) -> StrWithDeductionGuide<std::string>; // map char const * to std::string


int main() {

    {
        std::clog << "=== Non-Template Deduction Guides\n";
        
        //StrWithoutDeduction s1{"Non template deduction"}; // error: class template argument deduction failed
        //StrWithoutDeduction s2 = {"Non template deduction"}; // error: class template argument deduction failed
        //StrWithoutDeduction s3 = StrWithoutDeduction{"Non template deduction"}; // error: class template argument deduction failed
        //StrWithoutDeduction s4 = "Non template deduction"; // error: class template argument deduction failed:

        StrWithDeductionGuide    swd1{"Non template deduction"};
        static_assert(std::is_same_v<decltype(swd1), StrWithDeductionGuide<std::string>>);
        StrWithDeductionGuide    swd2 = {"Non template deduction"};
        static_assert(std::is_same_v<decltype(swd2), StrWithDeductionGuide<std::string>>);
        StrWithDeductionGuide    swd3 = StrWithDeductionGuide{"Non template deduction"};
        static_assert(std::is_same_v<decltype(swd3), StrWithDeductionGuide<std::string>>);
        
        // Note that aggregates need list initialization (the deduction works, but the initialization is not allowed)
        //StrWithDeductionGuide    swd4= "Non template deduction"; // error: conversion from 'const char [23]' to non-scalar type 'StrWithDeductionGuide<std::__cxx11::basic_string<char> >' requested
    }

	return 0;
}

/*******
    END OF FILE
*********/


