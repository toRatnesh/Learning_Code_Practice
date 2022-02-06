/***********
  This example demonstrates about CTRE lib.

  For more info visit:
	https://github.com/hanickadot/compile-time-regular-expressions
	Episode video:   https://www.youtube.com/watch?v=8aRfJp1oZGA&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=213
 **********/

#include <cassert>
#include <string>
#include <string_view>
#include <regex>
#include <ctre.hpp>

bool matchStdRegex(const std::string fp_str, const std::string fp_regex) {
	const std::regex lregex(fp_regex);
	return std::regex_match(fp_str, lregex);
}

bool matchCTRERegex(const std::string_view fp_str) {
	return ctre::match<"test number [0-9]{3}">(fp_str);
}

int main() {
	assert(matchStdRegex("test number 123", "test number [0-9]{3}") == true);
	assert(matchCTRERegex("test number 123") == true);
	return 0;
}


/******
  END OF FILE
 *****/



