/************
 *
 *	This example demonstrates why we can not move const value.
 *
 * *************/

#include <iostream>
#include <string>
#include <string_view>

size_t mylength(std::string && str) {
	return str.size();
}

int main() {
	std::string lstr("This is a sample string");
	const std::string cstr("This is a sample string");

	std::cout << mylength(std::move(lstr)) << '\n'; // std::string &&
	
	// moving from a const rvalue is meaningless
	// CE:  error: binding reference of type âd::string&& {aka std::basic_string<char>&&}âo âd::remove_reference<const std::basic_string<char>&>::type {aka const std::basic_string<char>}âiscards qualifiers
	//std::cout << mylength(std::move(cstr)) << '\n'; // const std::string &&

	return 0;
}

/***********
 *	END OF FILE
 * **********/

