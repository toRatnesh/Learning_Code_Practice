/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/type_traits

Chapter 21 Type Traits Extensions

C++17 extends the general abilities to use type traits (standard type functions) 
and introduces some new type traits

21.2 New Type Traits
	New type traits
		bool_constant
		has_unique_object_representations
		is_aggregate
	  
		is_swappable_with
		is_swappable
		is_nothrow_swappable_with
		is_nothrow_swappable

		is_invocable
		is_invocable_r
		is_nothrow_invocable
		is_nothrow_invocable_r
		
		invoke_result
	
	Deprecated 
		is_literal_type
		result_of


****************/

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <complex>

class S1 {
    public:
    ~S1()   {}
    S1()    {}
};

class S2 {
    public:
    ~S2();
    S2();
};
S2::~S2()   {}
S2::S2()    {}

template<typename T>
struct D1 : std::string, std::complex<T> {
    S1 s;
};

template<typename T>
struct D2 : std::string, std::complex<T>, S2 {

};

int fun(int val) {
    return val * 2;
}

int fun_noexcept(int val) noexcept {
    return val * 2;
}

int main() {
    std::cout << "=== new type traits ===\n";
    {
    std::cout << "\n=== std::is_aggregate<> ===\n";
    S1 s1{};
    D1<double>   dobj1{"sample string", {4.5, 7.8}, s1};
    std::cout << "std::is_aggregate_v<decltype(dobj1)>: " << std::boolalpha << std::is_aggregate_v<decltype(dobj1)> << '\n';

    S2 s2{};
    D2<double>   dobj2{"sample string", {4.5, 7.8}, s2};
    std::cout << "std::is_aggregate_v<decltype(dobj2)>: " << std::boolalpha << std::is_aggregate_v<decltype(dobj2)> << '\n';
    }

    {
    std::cout << "\n=== std::is_invocable<> ===\n";
	std::cout << "std::is_invocable_v<decltype(fun), int>: " << std::boolalpha << std::is_invocable_v<decltype(fun), int> << '\n';
	std::cout << "std::is_invocable_r_v<int, decltype(fun), int>: " << std::boolalpha << std::is_invocable_r_v<int, decltype(fun), int> << '\n';
	std::cout << "std::is_nothrow_invocable_v<decltype(fun), int>: " << std::boolalpha << std::is_nothrow_invocable_v<decltype(fun), int> << '\n';
	std::cout << "std::is_nothrow_invocable_r_v<int, decltype(fun), int>: " << std::boolalpha << std::is_nothrow_invocable_r_v<int, decltype(fun), int> << '\n';
	std::cout << '\n';
	std::cout << "std::is_invocable_v<decltype(fun_noexcept), int>: " << std::boolalpha << std::is_invocable_v<decltype(fun_noexcept), int> << '\n';
	std::cout << "std::is_invocable_r_v<int, decltype(fun_noexcept), int>: " << std::boolalpha << std::is_invocable_r_v<int, decltype(fun_noexcept), int> << '\n';
	std::cout << "std::is_nothrow_invocable_v<decltype(fun_noexcept), int>: " << std::boolalpha << std::is_nothrow_invocable_v<decltype(fun_noexcept), int> << '\n';
	std::cout << "std::is_nothrow_invocable_r_v<int, decltype(fun_noexcept), int>: " << std::boolalpha << std::is_nothrow_invocable_r_v<int, decltype(fun_noexcept), int> << '\n';
    }
    
    return 0;
}

/**********
    END OF FILE
****************/


