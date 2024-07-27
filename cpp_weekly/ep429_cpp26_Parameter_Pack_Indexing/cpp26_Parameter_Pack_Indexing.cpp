/*****

ep429_cpp26_Parameter_Pack_Indexing

References:
episode:    https://www.youtube.com/watch?v=wl7uWes7Sys
https://en.cppreference.com/w/cpp/26

This example demonstrates about C++26 parameter pack index

Pack indexing is a pack expansion of the unexpanded parameter pack 
followed by an ellipsis and index inside the subscript.
There are two kinds of pack indexing: 
    1. pack indexing expression
    2. pack indexing specifier

**********/

#include <cstdlib>
#include <print>

template<std::size_t index, typename ... T>
auto fun(T ... arg) {
    return arg...[index];
}


int main() {

    {
        auto ret = fun<0>("C++26", "parameter pack");
        std::println("{}", ret);
    }
    {
        auto ret = fun<1>("C++26", "parameter pack");
        std::println("{}", ret);
    }
    {
        auto ret = fun<2>("C++26", "parameter pack", "index");
        std::println("{}", ret);
    }
    {
        auto ret = fun<2>("C++26", "parameter pack", 2);
        std::println("{}", ret);
    }
    {
        //auto ret = fun<3>("C++26", "parameter pack", 2);    // CE error: invalid index 3 for pack arg of size 3
        //std::println("{}", ret);
    }

    return 0;
}

/*****
    END OF FILE
**********/


