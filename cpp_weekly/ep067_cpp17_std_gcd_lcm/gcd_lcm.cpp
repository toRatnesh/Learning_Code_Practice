/**************
 *
 * 	This example demonstrates the use of std::gcd() and std::lcm() to find out gcd and lcm of two numbers.
 *
 * ************/

#include <iostream>
#include <numeric>

int main() {
	std::cout << std::gcd(480, 340) << '\n';
	std::cout << std::lcm(480, 340) << '\n';

	std::cout << std::gcd(0, 0) << '\n';
	std::cout << std::lcm(0, 0) << '\n';

	// error: static assertion failed: gcd arguments are integers
	//std::cout << std::gcd(480, 10.8) << '\n';
	// error: static assertion failed: lcm arguments are not bools
	//std::cout << std::lcm(12, true) << '\n';

	return 0;
}

/******
 *	END OF FILE
 * *****/
