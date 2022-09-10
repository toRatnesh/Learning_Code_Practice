/***************
  This example demonstrates how a string can be spplit in to multiple strings using range

  This gives a range of ranges 

 *******************/


#include <fmt/format.h>
#include <iostream>
#include <ranges>
#include <string_view>

int main() {

    auto tokens = std::string_view{"This will be splited in multiple string"} | std::ranges::views::split(' ');
    // tokens is range of ranges
    // token is a subrange

    for(const auto & token : tokens) {
        //std::clog << std::string_view(token.begin(), token.end()) << '/'; // C++20
        std::clog << std::string_view{token} << '/';  // C++23
        //fmt::print("{}/", token); // C++23
    }

    std::clog << '\n';

    constexpr static auto tokens_02 = std::string_view{"This will be splited in multiple string"} | std::ranges::views::split(' ');
    for(const auto & token : auto{tokens_02}) {
        //std::clog << std::string_view(token.begin(), token.end()) << '/'; // C++20
        std::clog << std::string_view{token} << '/';  // C++23
        //fmt::print("{}/", token); // C++23
    }

    return 0;
}

/********
  END OF FILE
 ********/


