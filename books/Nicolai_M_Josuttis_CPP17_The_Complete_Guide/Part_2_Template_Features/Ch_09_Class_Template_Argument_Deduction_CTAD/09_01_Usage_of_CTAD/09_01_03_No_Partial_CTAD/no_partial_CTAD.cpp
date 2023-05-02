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


9.1.3 No Partial Class Template Argument Deduction
    unlike function templates, class template arguments may not be partially deduced (by explicitly specifying only some of the template arguments).
    Due to this We still can’t easily use a lambda to specify the sorting criterion of an associative container or the hash function of an unordered container (since c++20 it is possible).

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

template<typename T1, typename T2, typename T3=T2>
auto function_template(T1 t1 = T1{}, T2 t2 = T2{}, T3 t3= T3{}) {
    std::clog << t1 << ',' << t2 << ',' << t3 << std::endl;
}

template<typename T1, typename T2, typename T3=T2>
class ClassTemplate {
    T1 t1; T2 t2; T3 t3;
    public:
    ClassTemplate(T1 t1 = T1{}, T2 t2 = T2{}, T3 t3= T3{}) 
        : t1(t1), t2(t2), t3(t3) { }
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
        std::clog << "=== CTAD No Partial Class Template Argument Deduction \n";
        const std::string astr = "sample string";
        {
            ClassTemplate ct1(1, 2.5, astr);
            ClassTemplate ct2(1, astr);
            //ClassTemplate ct3(1);

            function_template(1, 2.5, astr);
            //function_template(1, "sample string"); // this is causing issue with print for others
            function_template(1, astr);
            //function_template(1);
        }
        {
            ClassTemplate<int, double, std::string> ct1(1, 2.5, astr);
            ClassTemplate<int, std::string> ct2(1, astr);
            ClassTemplate<int, int> ct3(1, 2, 3);
            ClassTemplate<int, int> ct4(1, 2);
            //ClassTemplate<int> ct5(1, 2.5, "sample string"); // error: wrong number of template arguments (1, should be at least 2)

            function_template<int, double, std::string>(1, 2.5, astr);
            function_template<int, std::string>(1, astr);
            function_template<int, int>(1, 2, 3);
            function_template<int, int>(1, 2);
            function_template<int>(1, 2.5, astr);
        }
        {
            //ClassTemplate<> ct1(1, 2.5, "sample string");     // error: wrong number of template arguments (0, should be at least 2)
            //ClassTemplate<> ct2(1, "sample string");          // error: wrong number of template arguments (0, should be at least 2)

            function_template<>(1, 2.5, astr);
            function_template<>(1, astr);
        }
    }

	return 0;
}

/*******
    END OF FILE
*********/
