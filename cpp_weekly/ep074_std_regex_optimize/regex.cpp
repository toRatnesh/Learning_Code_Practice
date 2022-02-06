/*******************
 *	This example demonstrates the use std::regex_constants::optimize.
 *	std::regex_constants::optimize
 *	Instructs the regular expression engine to make matching faster, with the potential cost of making construction slower. 
 *	For example, this might mean converting a non-deterministic FSA to a deterministic FSA.
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
			std::regex_constants::ECMAScript | std::regex_constants::icase | std::regex_constants::optimize);

	if(std::regex_search(s_look_into, look_for_regex)) {
		std::cout << "Text contains the phrase 'regular expressions'\n";
	}

	return 0;
}

/********
 *	END OF FILE
 * ********/
