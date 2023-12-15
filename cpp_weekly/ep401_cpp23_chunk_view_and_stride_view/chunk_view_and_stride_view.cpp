/*****

Reference
    episode https://www.youtube.com/watch?v=3ZeV-F1Rbaw
    https://en.cppreference.com/w/cpp/ranges/chunk_view
    https://en.cppreference.com/w/cpp/ranges/stride_view

This example demonstrates about C++23 chunk_view and stride_view

chunk_view
    std::ranges::views::chunk
    std::ranges::chunk_view

    chunk_view takes a view and a number n and produces a range of views (the chunks) of the original view, such that each chunk, except maybe the last one, has the size n. These chunks are non-overlapping, successive sub-ranges of the elements of the original view, in order.
    Let s be the size of the original view. If s is not the multiple of n, the size of the last produced view is exactly s % n (the remainder). Otherwise, the size of each chunk, including the last one, is n.
    The size of produced view is __div_ceil(s).
    If the n is not greater than ​0​ the behavior is undefined.    

stride_view
    std::ranges::views::stride
    std::ranges::stride_view

    stride_view is a range adaptor that takes a view and a number n and produces a view, that consists of elements of the original view by advancing over n elements at a time. This means that each mth element of the produced view is (n * i)th element of the original view, for some non-negative index i. The elements of the original view, whose "index" is not a multiple of n, are not present in the produced view.
    Let S be the size of the original view. Then the size of produced view is:
        (S / n) + (S % n ? 1 : 0), if S >= n; otherwise,
        1, if S > 0; otherwise,
        ​0​, and the resulting view is empty.

**********/

#include <iostream>
#include <array>
#include <ranges>
#include <format>

int main() {
    const std::array arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    {
        std::cout << "\n=== std::ranges::views::stride ===\n";
        for(const auto & elem : std::ranges::views::stride(arr, 3)) {
            std::cout << std::format("{:>4}", elem);
        }
        std::cout << '\n';
    }

    {
        std::cout << "\n=== std::ranges::stride_view ===\n";
        for(const auto & elem : std::ranges::stride_view(arr, 3)) {
            std::cout << std::format("{:>4}", elem);
        }
        std::cout << '\n';
    }

    {
        std::cout << "\n=== std::ranges::views::stride ===\n";
        for(const auto & elem : arr | std::ranges::views::stride(3)) {
            std::cout << std::format("{:>4}", elem);
        }
        std::cout << '\n';
    }


    {
        std::cout << "\n=== std::ranges::views::chunk ===\n";
        for(const auto & chnk_view : std::ranges::views::chunk(arr, 3)) {
            for(const auto & elem : chnk_view) {
                std::cout << std::format("{:>4}", elem);
            }
            std::cout << '\n';
        }
    }

    {
        std::cout << "\n=== std::ranges::chunk_view ===\n";
        for(const auto & chnk_view : std::ranges::chunk_view(arr, 3)) {
            for(const auto & elem : chnk_view) {
                std::cout << std::format("{:>4}", elem);
            }
            std::cout << '\n';
        }
    }    


    {
        std::cout << "\n=== std::ranges::views::chunk ===\n";
        for(const auto & chnk_view : arr | std::ranges::views::chunk(3)) {
            for(const auto & elem : chnk_view) {
                std::cout << std::format("{:>4}", elem);
            }
            std::cout << '\n';
        }
    } 

    return 0;
}

/*****
    END OF FILE
**********/


