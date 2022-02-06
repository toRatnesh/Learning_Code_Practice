/***********
 *	This example demonstrates the use of C++17 std:string_view feature.
 *
 *	The class template basic_string_view describes an object that can refer to a constant contiguous sequence 
 *	of char-like objects with the first element of the sequence at position zero.
 *
 *	For more info check:
 *	https://en.cppreference.com/w/cpp/string/basic_string_view
 *
 * **********/

#include <iostream>
#include <string>
#include <string_view>

size_t length(std::string_view str) 
//size_t length(const std::string & str) 
{
	return str.size();
}

int main() {
	std::cout << length("This is a sample string") << '\n';
	return 0;
}


/******
 *	END OF FILE
 * *******/
