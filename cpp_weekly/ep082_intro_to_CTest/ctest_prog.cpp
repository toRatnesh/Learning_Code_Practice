/*****************
 *	This example demonstrates the use of CMake CTest.
 *
 * *********************/

#include "ctest_prog.hpp"


int main() {

	if(is_even(7)) { 
		std::cout << "7 is an even number\n";
	}
	if(is_even(12)) { 
		std::cout << "12 is an even number\n";
	}
	std::cout << get_length(std::string("This is a sample string")) << '\n';
	return 0;
}

/*******
 *	END OF FILE
 * *********/

