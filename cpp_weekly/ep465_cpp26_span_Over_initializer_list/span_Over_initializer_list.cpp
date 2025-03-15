/*****

References

    episode https://www.youtube.com/watch?v=hWw_P6FUN_E
    https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2447r6.html

    This example demonstrates about std:span support for initilaizer list in C++26

**********/

#include <print>
#include <span>

void display(const std::span<const int> data) {
    for(const auto & elem : data) {
        std::print("{} ", elem);
    }
    std::println("");
}

int main() {
    // C++23 CE error: could not convert '{1, 2, 3, 4, 5}' from '<brace-enclosed initializer list>' to 'std::span<const int>'
    // display({1, 2, 3, 4, 5});
    display(std::array{1, 2, 3, 4, 5}); // C++23 OK

    display({1, 2, 3, 4, 5});

    return 0;
}

/*****
    END OF FILE
**********/

