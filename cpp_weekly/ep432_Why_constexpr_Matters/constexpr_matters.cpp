/*****

    ep432_Why_constexpr_Matters

    References
    episode https://www.youtube.com/watch?v=QZxfyGmpanM


    This example demonstrates how moving things which
    can be done at compile will improve performace

    Example code ia taken from
    episode 426 - Lambdas As State Machines

**********/

#include <cassert>
#include <cstdio>
#include <expected>
#include <print>

constexpr auto make_int_parser() {
    enum State { Startup, Numbers, Invalid };

    return [value = 0, state = Startup, is_negative = false](
               const char input) mutable -> std::expected<int, char> {
        switch (state) {
            case Startup:
                if (input == '-') {
                    is_negative = true;
                    state = Numbers;
                    return value;
                }
                [[fallthrough]];
            case Numbers:
                if (input >= '0' && input <= '9') {
                    value *= 10;
                    value += static_cast<int>(input - '0');
                    return ((is_negative == true) ? (value * -1) : value);
                } else {
                    state = Invalid;
                    return std::unexpected(input);
                }
            case Invalid:
                return std::unexpected(input);
        };

        return std::unexpected(input);
    };
}

consteval auto start_parsing() {
    auto parser = make_int_parser();

    parser('-');
    parser('3');
    parser('2');

    return parser;
}

int main() {
    auto parser = start_parsing();
    parser('1');
    parser('2');
    auto result = parser('0');
    return *result;
}

/*****
    END OF FILE
**********/


