/***********

    This example demonstrates about pitfalls of returning references
    And why they should be avoided
    
    If reference is returned make sure that the object it points to remains valid 
    till the time refernce is valid for use

****************/

#include <iostream>
#include <span>

int & get_int() {
    int val = 10;
    return val;
}

auto get_lambda() {
    int val = 11;

    return [&](){ return val + 2; };
}

std::string_view get_str_view() {
    std::string str{"this will be lost"};
    return str;
}

std::span<std::byte> get_span() {
    std::array<std::byte, 5> arr{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}, std::byte{5}};
    return arr;
}

int main() {

    std::cout << "get_int() " << get_int() << '\n';
    std::cout << "get_lambda()() " << get_lambda()() << '\n';
    std::cout << "get_str_view() " << get_str_view() << '\n';
    std::cout << "get_span() \n";
    for(auto & elem : get_span()) {
        std::cout << std::to_integer<int>(elem) << ' ';
    }
    std::cout << '\n';

    return 0;
}

/***********
    END OF FILE
****************/


