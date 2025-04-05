/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.
	
3.5 A view into a range

	Thanks to a component called a view, ranges are cheap, fast, and can reduce memory allocations.
	While std::string_view is specialized for strings, the views from ranges are generic.
	
	A view pulls the data only when needed making a view a lazy range that is cheap to create. 
	
	It must have move construction, move assignment, and destruction with a constant time.
	So all these methods should have O(1).
	Optionally a view can have a copy constructor and copy assignment operator if they satisfy O(1) as well.
	
	The primary goal of views is to be cheap and fast such that all operations have a constant time.
	Sometimes people refer to this as the pull model because the data is pulled when needed.
	
	They are only views of some other data.
	A view doesn’t own its elements! We have to ensure that the data a view uses lives longer than the view itself.
	Otherwise, we have UB.
	
	auto results =	numbers | 
					std::views::filter(is_odd) | 
					std::views::transform([](int n) { return n * 2; });	
					
	numbers	<--Pull--	filter	<--Pull--	transform

**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {
    const std::vector<int>    num_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    {
        auto res_vec =	num_vec | 
            std::views::filter([](const int val){ return (val & 1); }) | 
            std::views::transform([](const int val) { return (val * 2); });	

        for(const auto & elem : res_vec) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    {
        auto res_vec =	num_vec | 
            std::views::take_while([](const int val) { return (val < 5); });	

        for(const auto & elem : res_vec) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    {
        auto res_vec =	num_vec | 
            std::views::take_while([](const int val) { return (val > 5); });	

        for(const auto & elem : res_vec) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    for(const auto & elem : num_vec) {
        std::cout << elem << ',';
    }
    std::cout << '\n';

	return 0;
}

/*****
    END OF FILE
**********/

