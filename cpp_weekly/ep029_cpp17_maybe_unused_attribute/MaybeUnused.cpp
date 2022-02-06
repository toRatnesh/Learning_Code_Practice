/********
 * 	This examplde will demonstrate the use of CPP-17 [[maybe_unused]] attribute. 
 * 	Suppresses warnings on unused entities.  
 *********/

#include <iostream>

// warning: attribute ignored in declaration of 'struct s' [-Wattributes]
//[[maybe_unused]] struct s 

struct [[maybe_unused]] s 
{
	int m;
};

[[maybe_unused]] bool x_isEven(const int num) {
	return 0 == (num % 2); 
}

int main() {

	// this will generate warning for unused variable
	int i = 0;

	// this will not generate warning for unused variable becaause variable is declared as [[maybe_unused]]
	[[maybe_unused]] int j = 0;

	// this will not generate warning for unused variable because struct s is declared as [[maybe_unused]] 
	struct s sv;

	return 0;
}

/*** 
 * END OF FILE 
 * ***/
