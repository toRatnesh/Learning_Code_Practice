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

9.2.1 Using Deduction Guides to Force Decay
	one useful application of deduction guide is to ensure that a template parameter T decays while it is deduced
	when passing arguments of a template type, by reference, the parameter type doesn’t decay
	in this case we can write deduction guide to deduce decay type

*************/

#include <iostream>
#include <utility>

template<typename T1, typename T2>
class PairUsingReference {
    T1 first;
    T2 second;
    public:
    // when passing arguments of a template type, by reference, the parameter type doesn’t decay
    PairUsingReference(const T1 & f, const T2 & s) : first{f}, second{s} { }
};

template<typename T1, typename T2>
class PairUsingReferenceWithDeductionGuide {
    T1 first;
    T2 second;
    public:
    // when passing arguments of a template type, by reference, the parameter type doesn’t decay
    PairUsingReferenceWithDeductionGuide(const T1 & f, const T2 & s) : first{f}, second{s} { }
};
// Using Deduction Guides to Force Decay in case construtor takes template parameter by reference
template<typename T1, typename T2>
PairUsingReferenceWithDeductionGuide(T1, T2) -> PairUsingReferenceWithDeductionGuide<T1, T2>;

template<typename T1, typename T2>
class PairUsingCopy {
    T1 first;
    T2 second;
    public:
    PairUsingCopy(T1 f, T2 s) : first{f}, second{s} { }
};

int main() {

    {
        std::clog << "=== Using Deduction Guides to Force Decay\n";

        // std::pair<> is declared so that the constructors take the arguments by reference
        [[maybe_unused]] std::pair apair("Learning", "CTAD");    // compiles because It uses deduction guides

        PairUsingCopy pair_using_copy("Learning", "CTAD");
        static_assert(std::is_same_v<decltype(pair_using_copy), PairUsingCopy<char const *, char const *>>);

        // error: invalid conversion from 'const char*' to 'char' [-fpermissive]
        //PairUsingReference pair_using_ref("Learning", "CTAD");

        PairUsingReferenceWithDeductionGuide pair_using_ref_with_dguide("Learning", "CTAD");
        static_assert(std::is_same_v<decltype(pair_using_ref_with_dguide), PairUsingReferenceWithDeductionGuide<const char *, const char *>>);
    }

	return 0;
}

/*******
    END OF FILE
*********/


