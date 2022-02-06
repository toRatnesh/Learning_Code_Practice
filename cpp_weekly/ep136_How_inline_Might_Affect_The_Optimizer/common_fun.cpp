
#include "inline_fun.hpp"
#include "common_fun.hpp"

// this definition is needed in each translation unit if function is only declared in header file
// inline int inline_square_fun(const int parm) { return parm*parm; }

int this_will_call_inline(const int parm) {

	return inline_square_fun(parm);
}

/******
 *	END OF FILE
 * ******/
