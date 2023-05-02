/*******

    This example demonstrates about way to write better main than traditional one
    For more info visit:
    episode https://www.youtube.com/watch?v=zCzD9uSDI8c

**********/

#include <iostream>
#include <string_view>
#include <span>
#include <vector>
#include <array>

int main(const int argc, const char * const argv[]) {
    [[nodiscard]] int better_main(std::span<const std::string_view> args) noexcept;

    // Method -1 | Using vector to string_view
    //std::vector<std::string_view> args(argv, std::next(argv, static_cast<ptrdiff_t>(argc)));

    // Method -2 | Using array to string_view
    std::array<std::string_view, 255> args;
    std::size_t arg_count = std::min(args.size(), static_cast<std::size_t>(argc));
    for(std::size_t i = 0; i < arg_count; ++i) {
        args[i] = std::string_view(*std::next(argv, static_cast<ptrdiff_t>(i)));
    }

    return better_main(args);
}


[[nodiscard]] int better_main(std::span<const std::string_view> args) noexcept {
    for(const auto & elem : args) {
        std::cout << elem << '\n';
    }
    return 0;
}

/*******
    END OF FILE
**********/



