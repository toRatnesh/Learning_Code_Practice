/*******
 *	
 *	This example demonstrates the use of cpp-11 string constructors which are confusing in  the way when they are used with
 *	string and char pointer parameters.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/string/basic_string/basic_string 
 *
 * ******/

#include <iostream>
#include <string>

int main() {

		const std::string lcs = "this is a constant string";
		const char * const lccp = "this is a constant char array";

		const std::string s1(lcs, 5);
		const std::string s2(lccp, 5);
		const std::string s3(5, 'A');

		std::cout << "s1 from string : " << s1 << '\n';
		std::cout << "s2 from string : " << s2 << '\n';
		std::cout << "s3 from string : " << s3 << '\n';

		return 0;
}


/****
 *	END OF FILE
 * ****/


