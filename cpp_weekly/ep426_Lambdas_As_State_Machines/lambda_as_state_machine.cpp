/*****

    ep426_Lambdas_As_State_Machines

    References
    episode https://www.youtube.com/watch?v=fZe7gNgjV4A


    This example demonstrates about use of lambda as state machine
    since lambda are functions that can carry state

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

int main() {
    auto parser = make_int_parser();

    auto result = parser('-');
    assert(*result == 0);
    result = parser('3');
    assert(*result == -3);
    result = parser('2');
    assert(*result == -32);
    std::print("{}", *result);
    return 0;
}

/*****
    END OF FILE
**********/
