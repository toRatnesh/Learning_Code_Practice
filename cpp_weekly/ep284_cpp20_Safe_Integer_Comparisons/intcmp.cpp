/***************
 *
 * 	This example demonstrates about cpp20 int compare utility.
 * 	Comparison between signed and unsigned int types may result into wrong output.
 * 	For C++20 int comparison functions:
 * 		negative signed integers always compare less than (and not equal to) unsigned integers: 
 * 		the comparison is safe against lossy integer conversion.
 *
 * 	For more info visit:
 * 	https://en.cppreference.com/w/cpp/utility/intcmp
 *
 * ******************/

#include <iostream>
#include <utility>

int get_int() { return -1; }
unsigned int get_ui() { return 1; }

int main() {

	std::cout << "(get_int() < get_ui()) : " << (get_int() < get_ui()) << '\n';

	std::cout << "static_cast<int>(get_ui()) : " << static_cast<int>(get_ui()) << '\n';
	std::cout << "(get_int() < static_cast<int>(get_ui()))  : " << (get_int() < static_cast<int>(get_ui())) << '\n';

	std::cout << "(static_cast<unsigned int>(get_int()) : " << static_cast<unsigned int>(get_int()) << '\n';
	std::cout << "(static_cast<unsigned int>(get_int()) < get_ui())  : " << (static_cast<unsigned int>(get_int()) < get_ui()) << '\n';

	std::cout << "std::cmp_less(get_int(), get_ui()) : " << std::cmp_less(get_int(), get_ui()) << '\n';
	std::cout << "std::cmp_less(get_ui(), get_int()) : " << std::cmp_less(get_ui(), get_int()) << '\n';

	return 0;
}


/****
 *	END OF FILE
 * ***/
