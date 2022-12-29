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

9.2.4 Explicit Deduction Guides
	A deduction guide can be declared as to be explicit
	explicit deduction guide ignored only for the cases, where the explicit would disable initializations or conversions

*************/

#include <iostream>
#include <string>

template<typename T>
struct StrWithDeductionGuide {
    T val;
};
StrWithDeductionGuide(char const *) -> StrWithDeductionGuide<std::string>; // map char const * to std::string

template<typename T>
struct StrWithExplicitDeductionGuide {
    T val;
};
explicit StrWithExplicitDeductionGuide(char const *) -> StrWithExplicitDeductionGuide<std::string>; // map char const * to std::string

template<typename T>
struct ExplicitDeducePointer {
    ExplicitDeducePointer(T ) { std::clog << "ExplicitDeducePointer(T )\n"; }    
    template<typename U>
    ExplicitDeducePointer(U ) { std::clog << "ExplicitDeducePointer(U )\n"; }    
};
template<typename T>
explicit ExplicitDeducePointer(T) -> ExplicitDeducePointer<T *>;

int main() {

    {
        std::clog << "=== Explicit Deduction Guides\n";

        StrWithDeductionGuide       swd2 = {"Non template deduction"};
        static_assert(std::is_same_v<decltype(swd2), StrWithDeductionGuide<std::string>>);

        // error: class template argument deduction for 'StrWithExplicitDeductionGuide<T>' failed: explicit deduction guide selected in copy-list-initialization
        //StrWithExplicitDeductionGuide swed1 = {"explicit template deduction"};
        StrWithExplicitDeductionGuide swed2{"explicit template deduction"};
        static_assert(std::is_same_v<decltype(swed2), StrWithExplicitDeductionGuide<std::string>>);
        StrWithExplicitDeductionGuide swed3 = StrWithExplicitDeductionGuide{"explicit template deduction"};
        static_assert(std::is_same_v<decltype(swed3), StrWithExplicitDeductionGuide<std::string>>);
        StrWithExplicitDeductionGuide swed4 = {StrWithExplicitDeductionGuide{"explicit template deduction"}};
        static_assert(std::is_same_v<decltype(swed4), StrWithExplicitDeductionGuide<std::string>>);


        ExplicitDeducePointer val_int_1{42};    // type ExplicitDeducePointer<int *> using deduction guide 
        static_assert(std::is_same_v<decltype(val_int_1), ExplicitDeducePointer<int *>>);
        ExplicitDeducePointer val_int_2 = 42;   // type ExplicitDeducePointer<int> using constructor 
        static_assert(std::is_same_v<decltype(val_int_2), ExplicitDeducePointer<int>>);

        int val = 62;
        ExplicitDeducePointer val_int_3{&val};  // type ExplicitDeducePointer<int **> using deduction guide 
        static_assert(std::is_same_v<decltype(val_int_3), ExplicitDeducePointer<int **>>);
        ExplicitDeducePointer val_int_4 = &val; // type ExplicitDeducePointer<int *> using constructor
        static_assert(std::is_same_v<decltype(val_int_4), ExplicitDeducePointer<int *>>);

    }

	return 0;
}

/*******
    END OF FILE
*********/


