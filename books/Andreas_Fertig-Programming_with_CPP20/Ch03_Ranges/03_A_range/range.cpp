/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.
	
3.3 A range

	A range is a type with an iterator pair consisting of a begin and end function.

	struct Range {
		T begin();
		T end();
	};

	The above range models a finite range.
	Here we usually compare begin and end for equality, and stop the iterations once that condition is true.

	For an infinite range, which is possible with ranges, the end type is usually a different one than that for begin. 
	The STL brings us a new type for convenience, std::default_sentinel_t.

	struct Range {
		T						begin();
		std::default_sentinel_t	end();
	};
	
3.3.1 What is a common_range?	
	
	A common_range, on the other hand, is a range where begin(r) and end(r) return the same type.
	This implies that a common_range’s end does not return a sentinel.
	All classic iterators are a common_range.

	we need to use std::views::common to help us in creating a common_range from a C++20 range.

3.3.2 A sized_range

	A sized_range knows its size in constant time, using the size member function.	
	
**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <numeric>

#include <forward_list>
#include <list>

int main() {
    
    const std::vector vec{1, 2, 3, 4, 5, 6, 7, 8 , 9};

    // error: no matching function for call to 'accumulate(__gnu_cxx::__normal_iterator<const int*, std::vector<int, std::allocator<int> > >, std::ranges::take_while_view<std::ranges::ref_view<const std::vector<int, std::allocator<int> > >, main()::<lambda(int)> >::_Sentinel<true>, int)'
    // take_while does not returns common_range so can't use begin and end on it
    //const auto rng = vec | std::views::take_while([](const int val) {return (val & 1);});

    // std::views::common creats a common_range from a C++20 range
    const auto rng = vec | 
        std::views::take_while([](const int val) {return (val < 5);}) |
        std::views::common;
    
    const auto res = std::accumulate(rng.begin(), rng.end(), 0);
    std::cout << "Result " << res << '\n';

    static_assert(
        std::ranges::sized_range<std::list<int>> and
        not std::ranges::sized_range<std::forward_list<int>>
    );

	return 0;
}

/*****
    END OF FILE
**********/

