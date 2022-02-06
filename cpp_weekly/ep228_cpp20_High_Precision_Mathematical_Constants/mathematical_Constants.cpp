/***************
 *	This example demonstrates the use of c++20 Mathematical constants.
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/header/numbers
 *
 * *************/

#include <iostream>
#include <cmath>
#include <numbers>
#include <iomanip>

int main() {
	std::cout << std::setprecision(20) << M_PI << '\n';
	std::cout << std::setprecision(20) << std::numbers::pi << '\n';
	std::cout << std::setprecision(20) << std::numbers::pi_v<float> << '\n';
	std::cout << std::setprecision(20) << std::numbers::pi_v<double> << '\n';
	std::cout << std::setprecision(20) << std::numbers::pi_v<long double> << '\n';
	std::cout << std::setprecision(20) << std::numbers::pi_v<long double> << '\n';

	return 0;
}

/*********
 *	END OF FILE
 * ***********/
