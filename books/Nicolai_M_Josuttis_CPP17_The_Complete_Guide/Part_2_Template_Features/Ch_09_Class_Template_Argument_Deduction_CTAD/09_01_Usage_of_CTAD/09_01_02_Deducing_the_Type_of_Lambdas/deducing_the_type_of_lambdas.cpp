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


9.1.2 Deducing the Type of Lambdas
    With CTAD, we can instantiate class templates with the type of a lambda (to be exact: the closure type of a lambda)

*************/

#include <iostream>
#include <complex>
#include <vector>
#include <utility>

template<typename T, int SZ>
class MyArray {
	public:
    	MyArray (T(&)[SZ]) { }
};

template<typename Callable>
class CallableCounter {
    Callable callable;
    long call_count = 0;
    public:
    CallableCounter(Callable cb) : callable(cb) { }

    template<typename ... Args>
    auto operator() (Args && ... args) {
        ++call_count;
        return callable(std::forward<Args>(args)...);
    }

    long count() const noexcept { return call_count; }
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
        std::clog << "=== CTAD Deducing the Type of Lambdas \n";
        CallableCounter cc1([](){ std::clog << "lambda-1\n"; });
        CallableCounter cc2([](){ std::clog << "lambda-2\n"; });

        cc1(); cc1(); cc1(); cc1();
        cc2(); cc2(); cc2();

        std::clog << "cc1 is called " << cc1.count() << " times\n";
        std::clog << "cc2 is called " << cc2.count() << " times\n";
    }

	return 0;
}


/*******
    END OF FILE
*********/
