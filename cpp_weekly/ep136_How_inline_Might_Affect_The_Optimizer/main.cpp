

#include <iostream>

#include "inline_fun.hpp"
#include "common_fun.hpp"

// this definition is needed in each translation unit if function is only declared in header file
//inline int inline_square_fun(const int parm) { return parm*parm; }

int main() {

	std::cout << this_will_call_inline(5) << '\n';

	std::cout << inline_square_fun(7) << '\n';

	return 0;	
}

/******
 *	END OF FILE
 * ******/
