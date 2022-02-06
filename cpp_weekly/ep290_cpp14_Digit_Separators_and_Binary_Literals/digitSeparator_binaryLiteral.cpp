/**********
 *	This example demonstrates the use of CPP-14 Binary literals and Digit separators.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/integer_literal
 *	https://en.cppreference.com/w/cpp/language/integer_literal#Single_quote
 *
 * **********/


#include <iostream>

int main() {
		const auto val = 0b1010'0111;
		std::cout << val << '\n';

		const auto val2 = 0xF1'A5'BC'B3;
		std::cout << val2 << '\n';

		return 0;
}

/***
 *	END OF FILE
 * ***/
