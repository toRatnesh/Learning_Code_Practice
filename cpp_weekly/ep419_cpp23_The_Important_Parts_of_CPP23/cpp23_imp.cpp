/*****

    This example demonstrates about important features of C++23

        1. print
            https://en.cppreference.com/w/cpp/header/print
        2. import
            https://en.cppreference.com/w/cpp/language/modules
        3. statck trace
            https://en.cppreference.com/w/cpp/error#Stacktrace
        4. flat_map and flat_set
            https://en.cppreference.com/w/cpp/header/flat_map
            https://en.cppreference.com/w/cpp/header/flat_set
        5. multi dimensional subscript operator
            https://en.cppreference.com/w/cpp/language/operators#Array_subscript_operator
        6. ranges upgrade
            https://en.cppreference.com/w/cpp/algorithm/ranges
        7. constexpr cmath
            https://en.cppreference.com/w/cpp/header/cmath
        8. expected
            http://en.cppreference.com/w/cpp/utility/expected
        9. generator    
            https://en.cppreference.com/w/cpp/coroutine/generator
        10. md_span
            https://en.cppreference.com/w/cpp/container/mdspan
        11. explicit this
            https://en.cppreference.com/w/cpp/language/member_functions#Explicit_object_member_functions
        12. size literal suffix
            https://en.cppreference.com/w/cpp/language/integer_literal#The_type_of_the_literal
        13. start_lifetime_as
            https://en.cppreference.com/w/cpp/memory/start_lifetime_as

**********/

#include <print>
#include <stacktrace>
//#include <flat_set>
#include <string>
#include <array>
#include <list>
#include <vector>
#include <ranges>
#include <cmath>
#include <expected>
#include <generator>

// 3. stack trace
void printStack() {
    //std::print("{}", std::stacktrace::current());
}

// 8. expected
std::expected<std::string, uint32_t> getValue(bool flag) {
    if(flag) {
        return "Desired value";
    } else {
        return std::unexpected(1);
    }
}

// 9. generator
std::generator<int> get_numbers(int n) {
    for( ; ; co_yield n++);
}

int main() {

    // 1. print
    std::println("=== print and println ===");
    std::print("Hello");
    std::print("{}\n", " world");
    std::println("Hello world");

    // 2. import std
    std::println("\n=== import std ===");
    // yet to support by compilers

    // 3. stack trace
    std::println("\n=== stack trace ===");

    // 4. flat_map and flat_set
    std::println("\n=== flat_map and flat_set ===");
    // yet to support by compilers

    // 5. multi dimensional subscript operator
    std::println("\n=== multi dimensional subscript operator ===");
    int marr[][3][3] = {   {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
                          {{11, 12, 13}, {14, 15, 16}, {17, 18, 19}}
                        };

    std::println("marr[0][1][2] {}", marr[0][1][2]);

    // 6. ranges upgrade
    std::println("\n=== ranges upgrade ===");
    std::array  arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector vec{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    std::list   lst{"string-1", "string-2", "string-3", "string-4", "string-5"};

    for(const auto &[e1, e2, e3] : std::ranges::views::zip(arr, vec, lst)) {
        std::println("{} {} {}", e1, e2, e3);
    }

    // 7. constexpr cmath
    std::println("\n=== constexpr cmath ===");
    constexpr auto res = fmax(2.2, 3.2);
    static_assert(res == 3.2);

    // 8. expected
    std::println("\n=== expected ===");
    {
        auto res = getValue(true);
        std::println("{}", res.value());
    }
    {
        auto res = getValue(false);
        std::println("{}", res.error());
    }

    // 9. generator
    std::println("\n=== generator ===");
    for(const int num : get_numbers(1) | std::views::take(10)) {
        std::print("{} ", num);
    }
    std::println("");

    // 10. md_span
    std::println("\n=== md_span ===");
    // yet to support by compilers

    // 11. explicit this
    std::println("\n=== explicit this ===");
    
    // 12. size literal suffix
    std::println("\n=== size literal suffix ===");
    auto size1 = 42z;       // signed size_t
    auto size2 = 42uz;      // size_t
    std::println("{} {}", size1, size2);
    
    // 13. start_lifetime_as
    std::println("\n=== start_lifetime_as ===");

    return 0;
}

/*****
    END OF FILE
**********/


