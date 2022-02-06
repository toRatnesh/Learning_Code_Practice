/*********
 *	This example demonstrates about cpp20 consteval specifier.
 *
 *	consteval - specifies that a function is an immediate function, that is, every call to the function must produce a compile-time constant
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/consteval
 *
 *	This example also demonstrates how consteval is different from constexpr.
 *
 * ***********/


#include <iostream>

consteval int consteval_sqrt(const int num) {
	return (num * num);
}

constexpr int constexpr_sqrt(const int num) {
	return (num * num);
}

int main (const int argc, const char * argv[]) {  

	int val11 = consteval_sqrt(2);
	//static_assert(4 == val11);              // error: non-constant condition for static assertion
	const int val12 = consteval_sqrt(3);
	static_assert(9 == val12);
	constexpr int val13 = consteval_sqrt(4);
	static_assert(16 == val13);

	int val21 = constexpr_sqrt(2);
	//static_assert(4 == val21);		// error: non-constant condition for static assertion
	const int val22 = constexpr_sqrt(3);
	static_assert(9 == val22);
	constexpr int val23 = constexpr_sqrt(4);
	static_assert(16 == val23);

	/*
	// error: 'argc' is not a constant expression
	// int val14 = consteval_sqrt(argc);
	//const int val15 = consteval_sqrt(argc);
	//constexpr int val16 = consteval_sqrt(argc);
	*/

	int val24 = constexpr_sqrt(argc);
	const int val25 = constexpr_sqrt(argc);
	//constexpr int val26 = constexpr_sqrt(argc);   // error: 'argc' is not a constant expression

	return 0;    
}


/*******
 *	END OF FILE
 * *********/
