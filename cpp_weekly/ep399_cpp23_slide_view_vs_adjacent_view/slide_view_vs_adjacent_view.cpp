/*****

Reference
    episode https://www.youtube.com/watch?v=czmGjH16Hb0
    https://en.cppreference.com/w/cpp/ranges/slide_view
    https://en.cppreference.com/w/cpp/ranges/adjacent_view


This example demonstrates about C++23 adjacent_view and slide_view

adjacent_view
    std::ranges::views::adjacent
    std::ranges::adjacent_view
    std::ranges::views::pairwise

    takes a view, and produces a view whose ith element (a "window") is 
    a std::tuple that holds N references to the elements of the original view, 
    from ith up to i + N - 1th inclusively

    Let S be the size of the original view. Then the size of produced view is:
        S - N + 1, if S >= N,
        ​0​ otherwise, and the resulting view is empty

    useful when the window size is known at compile time

slide_view
    std::ranges::views::slide
    std::ranges::slide_view

    takes a view and a number n and produces a view whose mth element (a "window") is 
    a view over the mth through (m + n - 1)th elements of the original view

    Let s be the size of the original view. Then the size of produced view is:
        s - n + 1, if s >= n,
        ​0​ otherwise, and the resulting view is empty

    useful when the window size is known at run time

**********/

#include <iostream>
#include <array>
#include <ranges>
#include <format>

int main() {
    std::array<int, 9> arr{1, 2, 3, 4, 5, 6, 7, 8, 9};

    {
        std::cout << "=== std::ranges::views::adjacent ===\n";
        auto adj_view = std::ranges::views::adjacent<3>(arr);
        for(auto [e1, e2, e3] : adj_view) {
            std::cout << std::format("{} {} {}\n", e1, e2, e3);
        }       
    }


    {
        std::cout << "\n=== std::ranges::views::slide ===\n";
        for(const auto & sld_view : std::ranges::views::slide(arr, 4)) {
            for(const auto & elem : sld_view) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        }

        std::cout << "\n=== std::ranges::views::slide ===\n";
        for(const auto & sld_view : arr | std::ranges::views::slide(4)) {
            for(const auto & elem : sld_view) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        }        
    }

    {
        std::cout << "\n=== std::views::slide ===\n";
        for(const auto & sld_view : std::views::slide(arr, 4)) {
            for(const auto & elem : sld_view) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        }

        std::cout << "\n=== std::views::slide ===\n";
        for(const auto & sld_view : arr | std::views::slide(4)) {
            for(const auto & elem : sld_view) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        }        
    }

    return 0;
}

/*****
    END OF FILE
**********/


