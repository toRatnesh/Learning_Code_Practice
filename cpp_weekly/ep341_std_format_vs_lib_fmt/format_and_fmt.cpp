/*************
  This example demonstrates about format anf fmt lib 
  For more info visit:
https://www.youtube.com/watch?v=zc6B-j0S9Iw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=344
https://en.cppreference.com/w/cpp/utility/format/format


1. As of today format is only available in MSVC, {fmt} is avaible 
2. format gets print in C++23, {fmt} has print
3. moves with C++ standard, is ABI stable
4. {fmt} has a lot of utility/functions/helpers
5. {fmt} has constexpr capability

 ***************/

#include <iostream>
#include <format>
#include <array>

#include <fmt/format.h>
#include <fmt/compile.h>

constexpr auto get_msg(const int episode) {
	std::array<char, 19> result{};
	fmt::format_to(result.begin(), FMT_COMPILE("This is episode {}"), episode);
	return result;
} 

int main() {

	std::clog << std::format("This is episode {}", 341) << '\n'; 
	std::puts(std::format("This is episode {}", 341).c_str());

	fmt::print("This is episode {}", 341);

	static constexpr auto msg = get_msg(341);
	std::puts(msg.data());

	return 0;
}

/*************
  END OF FILE
 *************/

