/*****************
 *	This example demonstrates the use of CMake CTest.
 *
 * *********************/

#include "ctest_prog.hpp"

bool is_even(const unsigned int num) {
	return (0 == (num % 2));
}

size_t get_length(const std::string & str) {
	return str.length();
}


/*******
 *	END OF FILE
 * *********/

