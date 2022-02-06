/**************
 *	This example demonstrates the use of function-try-block.
 *	function-try-block:
 *	The function-try-block is one of the alternative syntax forms for function-body, which is a part of function definition.
 *
 *	For more detail check:
 *	https://en.cppreference.com/w/cpp/language/function-try-block
 *
 * *****************/

#include <iostream>
#include <string>

struct S {
	std::string m;
	S(const std::string& str, int idx) try : m(str, idx) {
		std::cout << "S(" << str << ", " << idx << ") constructed, m = " << m << '\n';
	} catch(const std::exception& e) {
		std::cout << "S(" << str << ", " << idx << ") failed: " << e.what() << '\n';
	} // implicit "throw;" here
};

int main() {
	S s1{"ABC", 1}; // does not throw (index is in bounds)
	try {
		S s2{"ABC", 4}; // throws (out of bounds)
	} catch (const std::exception& e) {
		std::cout << "S s2... raised an exception: " << e.what() << '\n';
	}

	return 0;
}

/***************
 *	END OF FILE
 * **************/
