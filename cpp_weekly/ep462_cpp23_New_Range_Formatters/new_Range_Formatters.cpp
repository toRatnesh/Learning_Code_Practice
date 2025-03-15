/*****

References
    episode https://www.youtube.com/watch?v=G6hhZGUE9S4
    https://en.cppreference.com/w/cpp/utility/format/range_formatter

    std::range_formatter is a helper class template for implementing range std::formatter specializations.

**********/

#include <print>
#include <string>
#include <utility>
#include <array>
#include <vector>
#include <map>
#include <ranges>
#include <chrono>

int main() {

    std::pair   par{2, 3.5};
    std::tuple  tup(2, 6.9, 'A', "string-1");
    std::array  arr{1,2,3,4,5};
    std::vector vec{21, 56, 79, 84, 36, 47};
    std::map<std::string, std::string>    mmp{{"key-1", "val-1"}, {"key-2", "val-2"}, {"key-3", "val-3"}};

    std::println("Pair value, {}", par);
    std::println("Pair value, {:n}", par);
    std::println("Pair value, {:m}", par);

    std::println("Tuple value, {}", tup);
    std::println("Tuple value, {:n}", tup);
    // CE error: call to consteval function 'std::basic_format_string<char, std::tuple<int, double, char, const char *> &>::basic_format_string<char[18]>' is not a constant expression
    //std::println("Tuple value, {:m}", tup);

    std::println("Array value, {}", arr);
    std::println("Array value, {:n}", arr);
    // CE error: call to consteval function 'std::basic_format_string<char, std::array<int, 5> &>::basic_format_string<char[18]>' is not a constant expression
    //std::println("Array value, {:m}", arr);

    std::println("Vector value, {}", vec);
    std::println("Vector value, {:n}", vec);
    // CE error: call to consteval function 'std::basic_format_string<char, std::vector<int> &>::basic_format_string<char[19]>' is not a constant expression
    //std::println("Vector value, {:m}", vec);

    std::println("Map value, {}", mmp);
    std::println("Map value, {:n}", mmp);
    std::println("Map value, {:m}", mmp);
    std::println("Map value, {:m}", mmp | std::views::drop(1));

    std::map<std::string, 
        std::pair<int,
            std::map<std::chrono::time_point<std::chrono::system_clock>, std::vector<int>>
        >>  data;
    data["data-1"] = {1, {{std::chrono::system_clock::now(), {1, 2, 3, 4, 5}}}};
    std::println("Complex map value, {:m}", data);

    return 0;
}

/*****
    END OF FILE
**********/

