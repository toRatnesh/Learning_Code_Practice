/*****

References
    episode https://www.youtube.com/watch?v=MVXGdwREo_E
    https://en.cppreference.com/w/cpp/ranges/zip_view

std::ranges::views::zip, std::ranges::zip_view

    zip_view is a range adaptor that takes one or more views, 
    and produces a view whose ith element is a tuple-like value 
    consisting of the ith elements of all views. 
    The size of produced view is the minimum of sizes of all adapted views.

**********/
#include <iostream>
#include <string>
#include <array>
#include <list>
#include <vector>
#include <ranges>

int main() {
    std::array  arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector vec{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    std::list   lst{"string-1", "string-2", "string-3", "string-4", "string-5"};

    std::cout << "=== std::ranges::zip_view ===\n";
    for(const auto &[e1, e2, e3] : std::ranges::zip_view(arr, vec, lst)) {
        std::cout << e1 << ' ' << e2 << ' ' << e3 << '\n';
    }

    std::cout << "\n=== std::ranges::views::zip ===\n";
    for(const auto &[e1, e2, e3] : std::ranges::views::zip(arr, vec, lst)) {
        std::cout << e1 << ' ' << e2 << ' ' << e3 << '\n';
    }

    std::cout << "\n=== std::views::zip ===\n";
    for(const auto &[e1, e2, e3] : std::views::zip(arr, vec, lst)) {
        std::cout << e1 << ' ' << e2 << ' ' << e3 << '\n';
    }

    std::cout << "\n=== using tuple ===\n";
    for(const auto &elem : std::views::zip(arr, vec, lst)) {
        std::cout << get<0>(elem) << ' ' << get<1>(elem) << ' ' << get<2>(elem) << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/



