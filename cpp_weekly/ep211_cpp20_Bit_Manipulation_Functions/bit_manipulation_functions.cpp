/**************
 *	This example demonstrates the use of c++20 bit manipulation functions defined in c++20.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/header/bit
 *	https://en.cppreference.com/w/cpp/header/bitset
 *
 * *************/

#include <iostream>
#include <bit>
#include <bitset>

int main() {
	const int val = -5;
	uint8_t u8val = 12;

	std::bitset<8> b1(val);
	std::bitset<8> b2(6);
	std::bitset<8> b3("01011010");
	std::bitset<16> b4(u8val);

	std::cout << "b1.size(): " << b1.size() << " b1.count(): " << b1.count() << '\n';
	std::cout << "b2.size(): " << b2.size() << " b2.count(): " << b2.count() << '\n';
	std::cout << "b3.size(): " << b3.size() << " b3.count(): " << b3.count() << '\n';
	std::cout << "b4.size(): " << b4.size() << " b4.count(): " << b4.count() << '\n';

	//std::cout << "std::popcount(val): " << std::popcount(val) << '\n'; //  error: no matching function for call to 'popcount(const int&)'
	std::cout << "std::popcount(u8val): " << std::popcount(u8val) << '\n';
	std::cout << "std::popcount(11u): " << std::popcount(11u) << '\n';

	return 0;
}

/**********
 *	END OF FILE
 * *********/
