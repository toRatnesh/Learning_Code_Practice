/**************
 *	This example demonstrates raw string literals.
 *
 *	Raw string literal. Used to avoid escaping of any character. Anything between the delimiters becomes part of the string.
 *	
 *	For more info visit tutorial video:
 *	https://en.cppreference.com/w/cpp/language/string_literal
 *
 * *****************/

#include <iostream>
#include <string>

int main() {
	std::string lstr = R"(this is a sample string)";
	std::string lstr2 = R"thisisadelimiter(This is a raw string literl with a delimiter "thisisadelimiter"
		
		with a new line added to it 
		
		and prints it constents as it is 
		
		like this tab \t or linefeed \n or alarm \a
		
		end of this raw string literal.)thisisadelimiter";

	std::cout << lstr << '\n';
	std::cout << lstr2 << '\n';

	return 0;
}

/**********
 *	END OF FILE
 * *********/
