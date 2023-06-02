/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/type_traits

Chapter 21 Type Traits Extensions

C++17 extends the general abilities to use type traits (standard type functions) 
and introduces some new type traits

21.4 std::void_t<>

	std::void_t<> yields void for any variadic list of template parameters
	namespace std {
		template<typename...> using void_t = void;
	}
	
	This is helpful, where we only want to deal with types solely in an argument list
	Major application is the ability to check for conditions when defining new type traits
	
	// primary template:
	template<typename, typename = std::void_t<>>
	struct HasVarious : std::false_type { };
	
	// partial specialization (may be SFINAE’d away):
	template<typename T>
	struct HasVarious<T, std::void_t<decltype(std::declval<T>().begin()), 
		typename T::difference_type, 
		typename T::iterator>> : std::true_type { };

	HasVariousT<>, which checks for three things:
	member function begin()
	type member difference_type
	type member iterator
	
	The partial specialization is only used, when all the corresponding expressions are valid for a type T
	
	you can use std::void_t to easily define other traits checking for one or multiple conditions, 
	where the existence/ability of a member or operation matters

****************/

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <vector>

template<typename T, typename = std::void_t<>>
struct has_various : std::bool_constant<false> {};

template<typename T>
struct has_various<T, 
    std::void_t<decltype(std::declval<T>().begin()),
    typename T::difference_type,
    typename T::iterator>> : std::bool_constant<true> {    
};

template<typename T, typename = std::void_t<>>
struct has_display : std::bool_constant<false> {};

template<typename T>
struct has_display<T, 
    std::void_t<decltype(std::declval<T>().display())>> 
        : std::bool_constant<true> {    
};

class S {
    public:
    void display() {}
};

int main() {

    std::cout << "=== std::void_t<> ===\n";
    {
    std::cout << "has_various<S>::value: " << std::boolalpha << has_various<S>::value << '\n';
    std::cout << "has_various<std::vector<int>>::value: " << std::boolalpha << has_various<std::vector<int>>::value << '\n';
    std::cout << '\n';

    std::cout << "has_display<S>::value: " << std::boolalpha << has_display<S>::value << '\n';
    std::cout << "has_display<std::vector<int>>::value: " << std::boolalpha << has_display<std::vector<int>>::value << '\n';
    }

    return 0;
}

/**********
    END OF FILE
****************/


