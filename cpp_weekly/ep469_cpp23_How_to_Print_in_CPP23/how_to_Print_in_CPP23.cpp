/*****

References
    episode https://www.youtube.com/watch?v=s6CZmNOCoQU
    https://github.com/fmtlib/fmt

    This example demonstrates about how to print in different way in CPP 23

**********/

#include <iostream>
#include <print>

int main() {

    std::puts("use std::puts to print null terminated string with new line");
    
    std::print("use std::print to print with {} in {} {} without new line \n", "formatting", "C++", 23);

    std::println("use std::printin to print with {} in {} {} with new line", "formatting", "C++", 23);

    std::puts("use other libraries like fmt lib");

    return 0;
}

/*****
    END OF FILE
**********/

