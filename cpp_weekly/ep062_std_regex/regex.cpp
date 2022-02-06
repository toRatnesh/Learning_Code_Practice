/*******************
 *
 * 	Regular expressions library
 * 	The regular expressions library provides a class that represents regular expressions, 
 * 	which are a kind of mini-language used to perform pattern matching within strings.
 *
 *
 *
 * *********************/


#include <iostream>
#include <string>
#include <regex>

int main() {
	const std::string s_look_into = "Some people, when confronted with a problem, think "
		"\"I know, I'll use regular expressions.\" "
		"Now they have two problems.";

	std::regex look_for_regex("REGULAR EXPRESSIONS",
			std::regex_constants::ECMAScript | std::regex_constants::icase);

	if(std::regex_search(s_look_into, look_for_regex)) {
		std::cout << "Text contains the phrase 'regular expressions'\n";
	}

	return 0;
}

/********
 *	END OF FILE
 * ********/
