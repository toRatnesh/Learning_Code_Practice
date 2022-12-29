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

9.2.3 Deduction Guides versus Constructors
	CTAD uses the constructor/guide that has the highest priority according to overload resolution
	If a constructor and a deduction guide match equally well, the deduction guide is preferred
	It is usually fine to let the deduction guide take the argument by value (which also has the advantage to decay)

*************/

#include <iostream>
#include <string>

template<typename T>
class DeductionGuideVsConstructor {
    public:
    DeductionGuideVsConstructor(T const & ) {}
};
DeductionGuideVsConstructor(int) -> DeductionGuideVsConstructor<long>;

int main() {

    {
        std::clog << "=== Deduction Guides versus Constructors\n";
        
        DeductionGuideVsConstructor dvc_int(1);
        static_assert(std::is_same_v<decltype(dvc_int), DeductionGuideVsConstructor<long>>);
        DeductionGuideVsConstructor dvc_uint(1u);
        static_assert(std::is_same_v<decltype(dvc_uint), DeductionGuideVsConstructor<unsigned>>);
        DeductionGuideVsConstructor dvc_char('A');
        static_assert(std::is_same_v<decltype(dvc_char), DeductionGuideVsConstructor<char>>);
        const std::string cs{"sample string"};
        DeductionGuideVsConstructor dvc_cs(cs);
        static_assert(std::is_same_v<decltype(dvc_cs), DeductionGuideVsConstructor<std::string>>);
        DeductionGuideVsConstructor dvc_bool(true);
        static_assert(std::is_same_v<decltype(dvc_bool), DeductionGuideVsConstructor<bool>>);
    }

	return 0;
}


/*******
    END OF FILE
*********/


