/**************
 *	
 *	This example demonstrates the difference between positive 0 and negative 0.
 *
 * **************/


#include <iostream>
#include <cmath>

int main() {
	std::cout << 0 << '\n';
	std::cout << -0 << '\n';
	std::cout << std::signbit(0) << '\n';
	std::cout << std::signbit(-0) << '\n';
	std::cout << '\n';

	std::cout << 0.0 << '\n';
	std::cout << -0.0 << '\n';
	std::cout << std::signbit(0.0) << '\n';
	std::cout << std::signbit(-0.0) << '\n';
	std::cout << '\n';

	/*
	   std::cout << 1/0 << '\n';
	   std::cout << 1/-0 << '\n';
	   std::cout << std::signbit(1/0) << '\n';
	   std::cout << std::signbit(1/-0) << '\n';
	   std::cout << '\n';
	   */


	std::cout << 1/0.0 << '\n';
	std::cout << 1/-0.0 << '\n';
	std::cout << std::signbit(1/0.0) << '\n';
	std::cout << std::signbit(1/-0.0) << '\n';
	std::cout << '\n';


	return 0;
}

/*****
 *	END OF FILE
 * *****/
