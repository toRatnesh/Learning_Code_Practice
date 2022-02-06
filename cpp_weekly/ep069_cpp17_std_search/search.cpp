/****************
 *
 * 	This example demonstrates the use of std::search.
 * 	std::search
 * 	Searches for the first occurrence of the sequence of elements.
 * 	For more info check:
 * 	https://en.cppreference.com/w/cpp/algorithm/search
 *
 * ****************/

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

int main() {
	const std::string find_in = R"(This is a sample string which will be used to search a string to learn std::search and std::find)";
	std::string to_find = R"(sample)";

	auto lit = std::search(find_in.cbegin(), find_in.cend(), to_find.cbegin(), to_find.cend());
	if(find_in.cend() != lit) {
		std::cout << to_find << " found at offset " << (lit - find_in.cbegin()) << '\n';
	}
	else {
		std::cout << to_find << " not found." << '\n';
	}

	to_find = R"(std::search)";
	auto lit2 = std::search(find_in.cbegin(), find_in.cend(), 
			std::boyer_moore_searcher(to_find.cbegin(), to_find.cend()));
	if(find_in.cend() != lit2) {
		std::cout << to_find << " found at offset " << (lit2 - find_in.cbegin()) << '\n';
	}
	else {
		std::cout << to_find << " not found." << '\n';
	}

	return 0;
}

/*******
 *	END OF FILE
 * *********/
