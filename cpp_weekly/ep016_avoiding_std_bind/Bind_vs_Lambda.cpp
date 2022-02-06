/***********
 *
 * 	This example demonstrates how lambda can be used to replace the use of bind.
 * 	It also demonstrates how using lambda gives advantage of performance and better template friendly programming.
 *
 * 	Advantage of using lambda over bind:
 * 	1. Better compile time
 * 	2. Better execution time
 * 	3. Better friendness with template
 * 	4. Btter memory usage at compile time
 *
 * 	NOTE:
 * 		Always prefer lambda over bind.
 *
 * *********/

#include <iostream>
#include <string>
#include <functional>

void x_print(const int num, const std::string & str) {
	//std::cout << num << " -- " << str << '\n';
	return ;
}

int main() {
/*
	const auto fb = std::bind(x_print, 100, "Using bind");
	for(uint64_t i = 0; i < 1000000; ++i) {		
		fb();	
	}
*/
	const auto fl = [](const auto arg1, const auto arg2) { 
		x_print(arg1, arg2);
	};
	for(uint64_t i = 0; i < 1000000; ++i) {		
		fl(100, "Using lambda");	
	}

	return 0;
}

/*****
 *	EOF
 * ***/

