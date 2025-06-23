/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges
    https://en.cppreference.com/w/cpp/ranges#Range_concepts

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.

3.9 Views
		
	Views are a radical change in how we can use STL algorithms.
	They provide ondemand computation. 
	They generate their elements (iota) or refer to them from elsewhere.
	
**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {

    for (int i : std::views::iota(1, 10)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (int i : std::views::iota(1) | std::views::take(5)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::ranges::for_each(std::views::iota(1, 10),
                          [](const int i){ std::cout << i << ' '; });
    std::cout << '\n';

	return 0;
}

/*****
    END OF FILE
**********/

