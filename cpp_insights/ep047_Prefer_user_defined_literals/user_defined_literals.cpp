
/*****

    References:
    episode:    https://www.youtube.com/watch?v=30NFjhX__mM


    This example demonstrates to prefer user defined literals for following reasons
    1. better performance
    2. clean and better readable code

**********/

#include <iostream>
#include <string>

int main() {
    using namespace std::string_literals;

    auto str1 = std::string{"a string using std::string Hel\0lo"};
    auto str2 = "a string using string literal Hel\0lo"s;

    std::cout << str1 << '\n';
    std::cout << str2 << '\n';

    return 0;
}

/*****
    END OF FILE
**********/

