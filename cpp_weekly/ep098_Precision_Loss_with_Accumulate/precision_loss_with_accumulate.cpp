/***********************
 *	This example demostrates the precision losss due to use of std::accumulate 
 *	which main cause is impilicit conversion from one type to another type.
 *
 *	std::accumulate
 *	Computes the sum of the given value init and the elements in the range [first, last). 
 *	The first version uses operator+ to sum up the elements.
 *
 *	For more info check:
 *	https://en.cppreference.com/w/cpp/algorithm/accumulate
 *
 * 	NOTE:
 * 		operator+ results in precision loss due to impilicit conversion.
 *
 *
 * **************************/

#include <iostream>
#include <array>
#include <numeric>

int main() {
	std::array<double, 6> larr{1.2, 3.4, 5.6, 6.8, 7.2, 9.3};

	// this will result in precision lost because init value is double
	auto res = std::accumulate(larr.begin(), larr.end(), 0);
	std::cout << res << '\n';

	// this will not result in precision lost because init value is double
	auto res2 = std::accumulate(larr.begin(), larr.end(), 0.0);
	std::cout << res2 << '\n';

	// this demonstrates the impilicit conversion of double to int
	int val = larr[0];
	val += larr[1];

	return 0;
}

/***********
 *	END OF FILE
 * ******/
