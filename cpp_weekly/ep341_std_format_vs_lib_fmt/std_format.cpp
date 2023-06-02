/******

    This example demonstrates about std::format library and fmt lib
    
    References
    https://ggulgulia.medium.com/c-20-formatting-library-part1-setup-and-basics-dc523aca24de
    https://ggulgulia.medium.com/c-20-string-formatting-part-2-fill-and-alignment-dcc4588b0bdd

    For more info visit:
	https://www.youtube.com/watch?v=zc6B-j0S9Iw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=344
	https://en.cppreference.com/w/cpp/utility/format/format
	https://github.com/fmtlib/fmt


1. As of today format is only available in MSVC, {fmt} is avaible 
2. format gets print in C++23, {fmt} has print
3. moves with C++ standard, is ABI stable
4. {fmt} has a lot of utility/functions/helpers
5. {fmt} has constexpr capability


std::format 

Basics

    text formatting is done with the placeholder {} followed by the argument to it after the entire string
    placeholder is actually the point where all string formatting magic happens

    Argument index
        If there are multiple placeholders in the formatted string, 
        then the correct argument for a given placeholder can be passed by an optional index starting from 0
        Providing less number of arguments than the placeholders will result in compilation error
        Providing extra arguments than the placeholders will be ignored
    
    Escaping curly braces
        simply put two pairs of curly braces {{}} — one pair as the regular placeholder and the second pair for the escape sequence


Format Specifiers
    
    { arg-id (optional) }
    { arg-id (optional) : format-spec }

    The format specifiers are the manipulator tokens in the string formatting library that allows one to format the string in multiple ways.
    The format specifier has the following form
    [[fill]align][sign][0][#][width][precision][L][type]

Width format specifier
    Static width
    proivde the width in integer number, say widthto the placeholder after the colon ( {:width})
    
    Dynamic width
    provide extra placeholder curly braces after the colon (:) and additionally the argument index that refers to the integral value of width: {argument_idx:{width_idx}}

Fill-and-Align format specifier

    Default alignment (numbers and numbers)
        Rules for default alignment of numbers and text:
        Numbers: aligned to the end of formatted string
        Texts: aligned to the beginning of formatted string

    Alignment
        beginning   : {:<5}, where < indicates alignment to beginning and 5 indicates five spaces
        end         : {:>9}, where > indicates alignment to end and 9 indicates nine spaces
        center      : {:^8}, where < indicates alignment to center and 8 indicates eight spaces

    Filling
        The space or empty character can be replaced by any other character by specifying the character before the alignment specifier

*************/

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
	//std::puts(msg.data());	// causing program crash

    std::cout << std::format("Learning {} deriven from {}!\n", "standard format library", "fmt/lib");

    std::cout << std::format("=== Argument index ===\n");
    std::cout << std::format("{1} was introduced in standard C++ version {0}\n", "C++20", "standarad format library");
    //std::cout << std::format("{0} was introduced in standard C++ version {}\n", "standarad format library", "C++20"); // CE
    //std::cout << std::format("{1} was introduced in standard C++ version {0}\n", "C++20");    // CE
    std::cout << std::format("{1} was introduced in standard C++ version {0}\n", "C++20", "standarad format library", "extra argument");

    std::cout << std::format("=== Escaping curly braces ===\n");
    std::cout << std::format("C++ version {{20}} has introduced std::format lib\n");

    std::cout << std::format("\n=== Static width ===\n");
    std::cout << std::format("Student id is {:5}\n", 12);
    std::cout << std::format("Student name is {:5}\n", "sample student");

    std::cout << std::format("\n=== Dynamic width ===\n");
    const int width = 10;
    std::cout << std::format("Student id is {0:{1}}\n", 12, width);
    std::cout << std::format("Student name is {0:{1}}\n", "sample student", width);

    std::cout << std::format("\n=== Alignment ===\n");
    std::cout << std::format("Alignment is {}\n", "sample alignment");
    std::cout << std::format("Alignment is {:<30}\n", "sample alignment");
    std::cout << std::format("Alignment is {:>30}\n", "sample alignment");
    std::cout << std::format("Alignment is {:^30}\n", "sample alignment");

    std::cout << std::format("\n=== Filling ===\n");
    std::cout << std::format("Alignment is {}\n", "sample alignment");
    std::cout << std::format("Alignment is {:-<30}\n", "sample alignment");
    std::cout << std::format("Alignment is {:->30}\n", "sample alignment");
    std::cout << std::format("Alignment is {:-^30}\n", "sample alignment");

    return 0;
}

/******
    END OF FILE
*************/

