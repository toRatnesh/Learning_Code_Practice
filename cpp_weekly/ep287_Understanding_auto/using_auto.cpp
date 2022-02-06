/************
 *	This example demonstrates how type deduction for auto works.
 *
 *	Key Details:
 *	-> 'auto' uses the exact same rules as template type parameters
 *	-> 'auto' will never deduce a '&'
 *	-> 'const'-ness will be deduced (for references and pointers)
 *	-> value types are always copies
 *	-> auto will never perform a conversion
 *	-> auto is better performing because it eliminates accidental conversion
 *
 *	NOTE:
 *	1. auto type deduction is usually the same as template type deduction, but auto type deduction assumes 
 *	that a braced initializer represents a std::initializer_list, and template type deduction doesn't.
 *	2. auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
 *
 *	Refernce : Effective Modern C++
 *
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/auto
 *
 * 	Book reference:
 *	Effective Modern C++
 *	Item 2: Understand auto type deduction.
 *	CHAPTER 2 auto |
 *			Item 5: Prefer auto to explicit type declarations.
 *			Item 6: Use the explicitly typed initializer idiom when auto deduces undesired types
 *
 *
 *
 * **********/


#include <iostream>
#include <typeinfo>

int get_value() {
	int val = 5;
	return val;
}

int & get_ref() {
	static int val = 7;
	return val;
}

const int & get_cref() {
	static int val = 6;
	return val;
}


int main() {
	auto lv = get_value();
	auto lr = get_ref();
	auto lcr = get_cref();
	std::cout << typeid(lv).name() << '\n';
	std::cout << typeid(lr).name() << '\n';
	std::cout << typeid(lcr).name() << '\n';

	std::cout << "=========================\n";
	//auto & lv2 = get_value(); // error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
	const auto & lv2 = get_value();
	auto & lr2 = get_ref();
	auto & lcr2 = get_cref();
	std::cout << typeid(lv2).name() << '\n';
	std::cout << typeid(lr2).name() << '\n';
	std::cout << typeid(lcr2).name() << '\n';


	return 0;
}


/*****
 *	END OF FILE
 * *******/
