/*******

    This example demonstrates about new preprocessor directives
    C23     - #embed
    C++23   - #warning

    #embed


    #warning diagnostic-message
    After encountering the #warning directive, an implementation displays the message diagnostic-message and the program is not affected and the compilation continues.
    diagnostic-message can consist of several words not necessarily in quotes.

    For more info visit
    https://thephd.dev/finally-embed-in-c23
    https://en.cppreference.com/w/c/preprocessor/error
    https://en.cppreference.com/w/cpp/preprocessor/error
    episode https://www.youtube.com/watch?v=ibKnNRAq5UY

***********/

#include <iostream>
#include <string>

#ifndef COMPILE_TIME_INPUT
    #error "Error:    Compile time input file is not provided"
    #warning "Warning:  Compile time input file is not provided"
#endif

int main() {
    std::clog << __cplusplus << '\n';
    {
        static constexpr unsigned char json_data[] = {
            #embed "input.json"
        };
        std::clog << json_data << '\n';
    }

    {
        static constexpr unsigned char json_data[] = {
            #embed "input.json" limit(37)
        };
        std::clog << json_data << '\n';
        const std::string new_data(std::begin(json_data)+6, std::end(json_data)-5);
        std::clog << new_data << '\n';
    }

    return 0;
}

/***
    END OF FILE
*******/


