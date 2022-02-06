/**********
 *	This file has test cases.
 * **********/

#include "ctest_prog.hpp"

int main() {

	if(11 == get_length(std::string("Test_String"))) { 
		std::clog << "Get length: PASS\n";
	} else {
		std::clog << "Get length: FAIL\n";
	}

	if(11 != get_length(std::string("TestString"))) { 
		std::clog << "Get length: PASS\n";
	} else {
		std::clog << "Get length: FAIL\n";
	}


	if(true == is_even(6)) {
		std::clog << "Is even: PASS\n";
	} else {
		std::clog << "Is even: FAIL\n";
	}

	if(true != is_even(7)) {
		std::clog << "Is even: PASS\n";
	} else {
		std::clog << "Is even: FAIL\n";
	}

	return 0;
}

/*********
 *	END OF FILE
 * ***********/
