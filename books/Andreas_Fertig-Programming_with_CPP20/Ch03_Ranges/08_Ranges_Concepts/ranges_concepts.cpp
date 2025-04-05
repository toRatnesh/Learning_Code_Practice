/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges
    https://en.cppreference.com/w/cpp/ranges#Range_concepts

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.

3.8 Ranges Concepts

	Ranges are the first usage of Concepts.
	
**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

void display(std::ranges::common_range auto cont_view) {
    for(const auto & elem : cont_view) {
        std::cout << elem << ',';
    }
    std::cout << '\n';
}

int main() {
    const std::vector<int>  nums_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};


    {
        const auto res = nums_vec | 
            std::views::take_while([](const int val) { return (val < 6); });

        // CE because take_while does not gives common_range while display needs it
        //display(res);   // CE error: no matching function for call to 'display(const std::ranges::take_while_view<std::ranges::ref_view<const std::vector<int> >, main()::<lambda(int)> >&)'
    }

    {
        const auto res = nums_vec | 
            std::views::take_while([](const int val) { return (val < 6); }) |
            std::views::common;
            
        display(res);
    }

	return 0;
}

/*****
    END OF FILE
**********/

