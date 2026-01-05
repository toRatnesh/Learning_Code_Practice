/*****

References
    episode:    https://www.youtube.com/watch?v=u0mVnuUh46w
    https://en.cppreference.com/w/cpp/container/array.html
    https://en.cppreference.com/w/cpp/container/span.html

    This example demonstartes that std::array and std::span have better performance
    . array and span can have compile time size
    . they have contiguous memory

**********/

#include <iostream>
#include <ranges>
#include <algorithm>
#include <span>
#include <vector>

constexpr size_t ASIZE{10};

auto useArray(std::array<int, ASIZE> & data) {
    std::ranges::for_each(data, [](auto & val){ val = val * 2;});
}

auto useSpan(std::span<int> data) {
    std::ranges::for_each(data, [](auto & val){ val = val * 2;});
}

auto useVector(std::vector<int> & data) {
    std::ranges::for_each(data, [](auto & val){ val = val * 2;});
}

void display(const auto & data) {
    for(const auto & elem: data | std::views::take(10)) {
        std::cout << elem << ", ";
    }
    std::cout << '\n';
}

int main() { 
    {
        std::vector<int> data(ASIZE, 4);
        std::cout << "=== using vector ===\n";
        {
            display(data);
            useVector(data);
            display(data);            
        }

        {
            std::cout << "=== using span ===\n";
            display(data);
            useSpan(data);
            display(data);            
        }
    }

    {
        std::array<int, ASIZE> data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::cout << "=== using array ===\n";
        {
            display(data);
            useArray(data);
            display(data);            
        }

        {
            std::cout << "=== using span ===\n";
            display(data);
            useSpan(data);
            display(data);            
        }        
    }

    return 0; 
}

/*****
    END OF FILE
**********/


