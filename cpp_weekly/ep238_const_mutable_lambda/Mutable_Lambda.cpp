/********
 *
 * 	This example demonstrates the use of mutable lambda.
 * 	Mutable lambda can not be const.
 *
 * ******/

#include <iostream>

int main() {

	//const auto lambda_nonMutable = [i = 3]() { return ++i; };  // error: increment of read-only variable 'i'
	auto lambda_nonMutable = [i = 3]() { return i; };
	std::cout << lambda_nonMutable() << '\n';

	//const auto lambda_Mutable = [i = 3]() mutable { return ++i; }; // case -1
	auto lambda_Mutable = [i = 3]() mutable { return ++i; };
	std::cout << lambda_Mutable() << '\n';      // case -1: error: no match for call to '(const main()::<lambda()>) ()' 

	return 0;
}

/***
 *	END OF FILE
 * **/
