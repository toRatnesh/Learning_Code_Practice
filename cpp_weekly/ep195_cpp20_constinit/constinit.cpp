/***********
 *	This example demonstrates the use of c++20 constinit specifier.
 *
 *	For more info visit:
 *	Tutorial video:	https://www.youtube.com/watch?v=o0z3KT4gW7k&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=196
 *	https://en.cppreference.com/w/cpp/language/constinit
 *
 * *********/

#include <iostream>

int main() {

	constinit static int val = 5; 
	std::cout << val << '\n';
	++val;      // constinit is not constant
	std::cout << val << '\n';

	// constinit with const is equivalent to constexpr 
	// because it initilaizes at compile time due to constinit and is a constant value
	constinit const static int val2 = 10; 
	std::cout << val2 << '\n';
	//++val2; // CE error: increment of read-only variable 'val2'

	return 0;
}

/******
 *	END OF FILE
 * *****/
