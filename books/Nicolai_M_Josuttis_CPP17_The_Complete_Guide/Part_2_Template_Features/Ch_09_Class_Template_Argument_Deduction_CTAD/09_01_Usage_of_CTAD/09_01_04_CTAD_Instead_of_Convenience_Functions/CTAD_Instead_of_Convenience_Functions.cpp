/************

References
    C++17 - The Complete Guide | Nicolai M. Josuttis

9. Class Template Argument Deduction (CTAD)

    Since C++17, you do not need to specify the template arguments explicitly, if the constructor is able to deduce all template parameters using CTAD.
    std::complex c{5.1,3.3};			// OK: std::complex<double> deduced
    std::vector v2 {"hello", "world"};	// OK: std::vector<const char*> deduced

9.1 Usage of Class Template Argument Deduction

    can be used whenever the arguments passed to a constructor can be used to deduce the class template parameters
    std::complex c1{1.1, 2.2};	// deduces std::complex<double>
    std::complex c2 = {4.4};	// deduces std::complex<double>
    std::complex c3{5, 3.3};	// ERROR: attempts to int and double as T

    for templates there are no type conversions used to deduce template parameters

    Class template argument deduction for variadic templates is also supported.
    std::tuple t{42, 'x', nullptr};		// OK: std::tuple<int, char, std::nullptr_t> deduced

    You can also deduce non-type template parameters
    template<typename T, int SZ>
    class MyArray {
        public:
        MyArray (T(&)[SZ]) { }
    };

    MyArray mc{"hello"};


9.1.4 Class Template Argument Deduction Instead of Convenience Functions
    using CTAD we can get rid of several convenience function templates that only existed to be able to deduce the type of a class from the passed call arguments
    NOTE: sometimes the convenience functions did more than just deducing template parameters. std::make_pair() also decays, which especially means that the type of passed string literals is converted to const char*.

    sometimes, using CTAD, things get more complicated
    when passing arguments of a template type, by reference, the parameter type doesn’t decay

*************/

#include <iostream>
#include <complex>
#include <vector>
#include <utility>
#include <string>

template<typename T, int SZ>
class MyArray {
	public:
    	MyArray (T(&)[SZ]) { }
};

template<typename T1, typename T2>
class PairUsingReference {
    T1 first;
    T2 second;
    public:
    // when passing arguments of a template type, by reference, the parameter type doesn’t decay
    PairUsingReference(const T1 & f, const T2 & s) : first{f}, second{s} { }
};

template<typename T1, typename T2>
class PairUsingCopy {
    T1 first;
    T2 second;
    public:
    PairUsingCopy(T1 f, T2 s) : first{f}, second{s} { }
};

int main() {
    {
        std::clog << "=== CTAD\n";

        [[maybe_unused]] std::complex c1{1.2,1.3};
        static_assert(std::is_same_v<decltype(c1), std::complex<double>>);
        
        [[maybe_unused]] std::complex c2(2.2, 2.3);
        static_assert(std::is_same_v<decltype(c2), std::complex<double>>);
        
        [[maybe_unused]] std::complex c3 = 3.4;
        static_assert(std::is_same_v<decltype(c3), std::complex<double>>);

        [[maybe_unused]] std::complex c4 = {4.5};
        static_assert(std::is_same_v<decltype(c4), std::complex<double>>);
        
        //std::complex c5 = {5, 5.6}; // error: class template argument deduction failed

        [[maybe_unused]] std::tuple tup{1, 2.3, 'A', "sample char *", c1};
        static_assert(std::is_same_v<decltype(tup), std::tuple<int, double, char, char const *, std::complex<double>>>);

        [[maybe_unused]] MyArray mc{"hello"};
        static_assert(std::is_same_v<decltype(mc), MyArray<const char, 6>>);
    }

    {
        std::clog << "=== CTAD Class Template Argument Deduction Instead of Convenience Functions\n";

        std::vector<int> vec{1, 2, 3, 4, 5};
        [[maybe_unused]] auto l_pair = std::make_pair(vec.begin(), vec.end());
        [[maybe_unused]] std::pair pair_using_CTAD(vec.begin(), vec.end());
        
        auto pair_decay = std::make_pair("Learning", "CTAD");
        static_assert(std::is_same_v<decltype(pair_decay), std::pair<char const *, char const *>>);

        //PairUsingReference pair_using_ref("Learning", "CTAD"); // compilation error
        //static_assert(std::is_same_v<decltype(pair_using_ref), PairUsingReference<char [9], char [5]>>);

        PairUsingCopy pair_using_copy("Learning", "CTAD");
        static_assert(std::is_same_v<decltype(pair_using_copy), PairUsingCopy<char const *, char const *>>);

        // std::pair<> is declared so that the constructors take the arguments by reference
        [[maybe_unused]] std::pair apair("Learning", "CTAD");    // compiles because It uses deduction guides
    }

	return 0;
}

/*******
    END OF FILE
*********/


