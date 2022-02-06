/**************
 *	This example demonstrates the use of c++11 std::nextafter.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/numeric/math/nextafter
 *
 * **************/

#include <iostream>
#include <cmath>
#include <iomanip>

int main() {

	const auto f1_val = 1.1230078945f;
	const auto nf1_val = std::nextafter(f1_val, 0);
	const auto nf2_val = std::nextafter(f1_val, INFINITY);

	std::cout << std::setprecision(20) << "p_val: " << f1_val << "\nn_val: " << nf1_val << '\n';
	std::cout << '\n';
	std::cout << std::setprecision(20) << "p_val: " << f1_val << "\nn_val: " << nf2_val << '\n';

	std::cout << "=== USING DOUBLE ===\n";
	const auto d1_val = 1.1230078945;
	const auto nd1_val = std::nextafter(d1_val, 0);
	const auto nd2_val = std::nextafter(d1_val, INFINITY);

	std::cout << std::setprecision(20) << "p_val: " << d1_val << "\nn_val: " << nd1_val << '\n';
	std::cout << '\n';
	std::cout << std::setprecision(20) << "p_val: " << d1_val << "\nn_val: " << nd2_val << '\n';

	return 0;
}

/***********
 *	END OF FILE
 * *********/
