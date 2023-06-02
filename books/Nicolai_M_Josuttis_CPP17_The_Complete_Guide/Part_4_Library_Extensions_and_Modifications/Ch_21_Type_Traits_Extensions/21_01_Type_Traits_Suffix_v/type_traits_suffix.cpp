/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/type_traits

Chapter 21 Type Traits Extensions

C++17 extends the general abilities to use type traits (standard type functions) 
and introduces some new type traits

21.1 Type Traits Suffix _v

	Since C++17, use the suffix _v for all type traits yielding a value (as suffix _t for all type traits yielding a type)
	achieved by defining variable template for each standard type trait
	namespace std {
		template<typename T>
		constexpr bool is_const_v = is_const<T>::value;
	}
	
	as type traits are evaluated at compile time, you can use the result at compile time in a compile time if
	
	the suffix _v also can be used if type traits yield a non-Boolean value, such as std::extent<>,

****************/

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <optional>

template<typename T, bool = std::is_pointer_v<T>> 
class S {
    T m_val;
    public:
    S(T val) : m_val{val} { }
    void display() {
        std::cout << "value is " << m_val << '\n';
    }
};

// partial specialization for pointer types
template<typename T>
class S<T, true>  {
    T m_val;
    public:
    S(T val) : m_val{val} { }
    void display() {
        std::cout << "value is " << *m_val << '\n';
    }
};

int main() {

    {
    std::cout << "=== type_traits suffix _v ===\n";
    int         val;
    const int   cval{5};

    std::cout << "std::is_const_v<decltype(val)>: " << std::boolalpha << std::is_const_v<decltype(val)> << '\n';
    std::cout << "std::is_const_v<decltype(cval)>: " << std::boolalpha << std::is_const_v<decltype(cval)> << '\n';

    char arr[]  = "sample string";
    const char *str   = "sample string";
    std::cout << "std::is_array_v<decltype(arr)>: " << std::boolalpha << std::is_array_v<decltype(arr)> << '\n';
    std::cout << "std::is_array_v<decltype(str)>: " << std::boolalpha << std::is_array_v<decltype(str)> << '\n';
    std::cout << "std::is_pointer_v<decltype(str)>: " << std::boolalpha << std::is_pointer_v<decltype(str)> << '\n';
    }

    {
    std::cout << "\n=== type_traits in compile-time if ===\n";
    using my_optional_t = std::optional<std::string>;
    my_optional_t   opstr{"sample string"};
    int             ival = 6;

    auto lambda = [](auto val){
        if constexpr(std::is_same_v<decltype(val), int>) {
            std::cout << "int value: " << val << '\n';
        }
        else if constexpr(std::is_same_v<decltype(val), my_optional_t>) {
            std::cout << "std::optional value:  " << *val << '\n';
        }
    };
    lambda(ival);
    lambda(opstr);
    }

    {
    std::cout << "\n=== type_traits for non boolean value ===\n";
    int     ival;
    int     d1arr[3];
    int     d2arr[4][5];
    int     d3arr[6][7][8];
    
    std::cout << "std::rank_v<decltype(ival)>: " << std::rank_v<decltype(ival)> << '\n';
    std::cout << "std::rank_v<decltype(d1arr)>: " << std::rank_v<decltype(d1arr)> << '\n';
    std::cout << "std::rank_v<decltype(d2arr)>: " << std::rank_v<decltype(d2arr)> << '\n';
    std::cout << "std::rank_v<decltype(d3arr)>: " << std::rank_v<decltype(d3arr)> << '\n';

    std::cout << "std::extent_v<decltype(ival)>: " << std::extent_v<decltype(ival)> << '\n';
    std::cout << "std::extent_v<decltype(d1arr)>: " << std::extent_v<decltype(d1arr)> << '\n';
    
    std::cout << "std::extent_v<decltype(d2arr)>: " << std::extent_v<decltype(d2arr)> << '\n';
    std::cout << "std::extent_v<decltype(d2arr), 1>: " << std::extent_v<decltype(d2arr), 1> << '\n';

    std::cout << "std::extent_v<decltype(d3arr)>: " << std::extent_v<decltype(d3arr)> << '\n';
    std::cout << "std::extent_v<decltype(d3arr), 1>: " << std::extent_v<decltype(d3arr), 1> << '\n';
    std::cout << "std::extent_v<decltype(d3arr), 2>: " << std::extent_v<decltype(d3arr), 2> << '\n';
    }

    {
    std::cout << "\n=== type_traits for templates ===\n";
    int     ival{9};
    S<int>      sval {ival};    sval.display();
    S<int *>    pval {&ival};   pval.display();
    }

    return 0;
}

/**********
    END OF FILE
****************/


