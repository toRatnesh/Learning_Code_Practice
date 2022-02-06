/*********************************************
 *	This example is an extension of ep-06 on variadic template.
 *
 * ******************************************/

#include <iostream>
#include <sstream>
#include <initializer_list>

template<typename T>
void x_print(const T & data_to_print) {
	std::cout << data_to_print << '\n';
	return ;
}


/********************************
 *
 * 	We are utilizing here the use of comma operator 
 * 	1. In case of initializer list outer most braces are guaranteed to execute this in the order 
 * 		specified including parameter pack expansion
 * 	2. Things that are in the comma delimited sequence 
 * 		For example: in case of (x_print(params), 0) first x_print(params) will be executed 
 *
 * *****************************/

template<typename ... TV>
void variadic_template_print(const TV & ... params) {
	const auto lambda_print = [](const auto & data) {
			std::cout << data << '\n';
		};

	(void)std::initializer_list<int>{(x_print(params), 0)...};		// CASE-01 | using helper function to print
	(void)std::initializer_list<int>{(lambda_print(params), 0)...};		// CASE-02 | using lambda function to print
	(void)std::initializer_list<int>{(std::cout << params << '\n', 0)...};	// CASE-03 | using inline statement to print

	return ;
}

int main() {
	variadic_template_print("Learning variadic template", 'A', 121, 4.21);
	return 0;
}


/*******
 *	EOF
 **********/
