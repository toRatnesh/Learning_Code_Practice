/*****

References
    Effective Modern C++ | Scott Meyers

Item 2: Understand auto type deduction

	with only one curious exception, type deduction is template type deduction
	
	When a variable is declared using auto, 
	auto plays the role of T in the template, and the type specifier for the variable acts as ParamType
	
	Example:
	
	auto x = 27;
	
	template<typename T>
	void func_for_x(T param);
	func_for_x(27);
	
	const auto cx = x;
	
	template<typename T>
	void func_for_cx(const T param);
	func_for_cx(x);
	
	const auto& rx = x;
	
	template<typename T>
	void func_for_rx(const T& param);
	func_for_rx(x);
	
	In a variable declaration using auto, the type specifier takes the place of ParamType, so there are three cases for that, too:
	• Case 1: The type specifier is a pointer or reference, but not a universal reference.
	• Case 2: The type specifier is a universal reference.
	• Case 3: The type specifier is neither a pointer nor a reference.

	We’ve already seen examples of cases 1 and 3:
	auto x = 27;			// case 3		(auto is int, x's type is iny)
	const auto cx = x;		// case 3		(auto is int, x's type is const int)
	const auto& rx = x;		// case 1		(auto is int, x's type is const int &)
	
	
	Array and function names decay into pointers for non-reference type specifiers. 
	That happens in auto type deduction, too:
	
    const char carr[] = "a char array";
    auto arr = carr;		// const char *
    auto & rarr = carr;		// const char (&)[13]

	int fun(int a, double d) {}
    auto fp = fun;			// int(*)(int, double)
    auto & fr = fun;		// int(&)(int, double)

	EXCEPTION
	auto assumes that a braced initializer represents a std::initializer_list, but template type deduction doesn’t
	
	When an auto–declared variable is initialized with a braced initializer, the deduced type is an instantiation of std::initializer_list. 
	But if the corresponding template is passed the same initializer, type deduction fails, and the code is rejected.
	
	C++11 uniform initialization 
	using auto will deduce std::initializer_list
	
	NOTE:	
	C++14 auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.


**********/

#include <iostream>
#include <type_traits>

int fun(int , double ) { return 0; }

template<typename T>
void tfun(T ) { }

template<typename T>
void tfun2(std::initializer_list<T> ) { }

auto ret_auto( ) {
    // return {1, 2, 3};   // CE error: returning initializer list
}

int main() { 

    std::cout << "=== auto type deduction ===\n";


	auto x = 27;			// case 3		(auto is int, x's type is iny)
	const auto cx = x;		// case 3		(auto is int, x's type is const int)
	const auto& rx = x;		// case 1		(auto is int, x's type is const int &)

    static_assert(std::is_same_v<decltype(x), int>);
    static_assert(std::is_same_v<decltype(cx), const int>);
    static_assert(std::is_same_v<decltype(rx), const int &>);

    std::cout << std::boolalpha << "std::is_same_v<decltype(x), int>: " << std::is_same_v<decltype(x), int> << '\n';
    std::cout << std::boolalpha << "std::is_same_v<decltype(cx), const int>: " << std::is_same_v<decltype(cx), const int> << '\n';
    std::cout << std::boolalpha << "std::is_same_v<decltype(rx), const int &>: " << std::is_same_v<decltype(rx), const int &> << '\n';
    
    std::cout << "\n=== array and function decay to pointer in absence of reference ===\n";

    const char carr[] = "a char array";
    auto arr = carr;
    auto & rarr = carr;

    static_assert(std::is_same_v<decltype(arr), const char *>);
    static_assert(std::is_same_v<decltype(rarr), const char (&)[13]>);

    std::cout << std::boolalpha << "std::is_same_v<decltype(arr), const char *> " << std::is_same_v<decltype(arr), const char *> << '\n';
    std::cout << std::boolalpha << "std::is_same_v<decltype(rarr), const char (&)[13]> " << std::is_same_v<decltype(rarr), const char (&)[13]> << '\n';

    auto fp = fun;
    auto & fr = fun;

    static_assert(std::is_same_v<decltype(fp), int(*)(int, double)>);
    static_assert(std::is_same_v<decltype(fr), int(&)(int, double)>);

    std::cout << std::boolalpha << "std::is_same_v<decltype(fp), int(*)(int, double)>: " << std::is_same_v<decltype(fp), int(*)(int, double)> << '\n';
    std::cout << std::boolalpha << "std::is_same_v<decltype(fr), int(&)(int, double)>: " << std::is_same_v<decltype(fr), int(&)(int, double)> << '\n';

    {
        std::cout << "\n=== exception for auto type deduction ===\n";
        [[maybe_unused]] int a = 5;          // c++98 initialization
        [[maybe_unused]] int b(5);           // c++98 initialization
        [[maybe_unused]] int c = {5};        // c++11 uniform initialization
        [[maybe_unused]] int d{5};           // c++11 uniform initialization

        [[maybe_unused]] auto aa = 5;       // int         
        static_assert(std::is_same_v<decltype(aa), int>);

        [[maybe_unused]] auto ab(5);       // int         
        static_assert(std::is_same_v<decltype(ab), int>);

        [[maybe_unused]] auto ac = {5};     // std::initializer_list<int>
        static_assert(std::is_same_v<decltype(ac), std::initializer_list<int>>);

        [[maybe_unused]] auto ad{5};        // std::initializer_list<int>
        static_assert(std::is_same_v<decltype(ad), int>);
    }

    {
        std::cout << "\n=== auto and template type deduction difference ===\n";
        
        auto x = {1, 2, 3};     // std::initializer_list<int>
        static_assert(std::is_same_v<decltype(x), std::initializer_list<int>>);

        //tfun({1, 2, 3});    // CE error: no matching function for call to 'tfun(<brace-enclosed initializer list>)'
        
        tfun2({1, 2, 3});   // T is int and parm is std::initializer_list<int>
    }

    {
        std::cout << "\n=== auto in a function return type or a lambda parameter ===\n";

        auto lambda = [](auto parm){ };
        //lambda({1, 2, 3});  // CE error: no match for call to '(main()::<lambda(auto:1)>) (<brace-enclosed initializer list>)'

    }

    return 0; 
}

/*****
    END OF FILE
**********/
