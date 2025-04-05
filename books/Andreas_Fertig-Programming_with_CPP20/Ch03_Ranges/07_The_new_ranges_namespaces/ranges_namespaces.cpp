/*****

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/ranges
    https://en.cppreference.com/w/cpp/ranges#Range_adaptors

Chapter 3 | Ranges: The next generation STL

	Ranges are a new element of the STL that make using algorithms more concise and add the ability to write code in a functional style.

3.7 The new ranges namespaces

	The main namespace is ranges.
	There we find all the new ranges elements as well as the range-compatible algorithms. 
	Within this namespace, there is with views another namespace. All the range adaptors are located here. 
	The third namespace, std::views, is a shortcut to access the range adaptors.

	For example, std::ranges::take_view becomes std::views::take.
	Postfixing take with view in a namespace already called view is kind of redundant.
	Hence the naming pattern is to drop _view from an adaptor in std::ranges.
	
	Why the new namespace for ranges?
		The behavior and guarantees of some algorithms are different with ranges.
		
		In short, range algorithms are function objects compared to algorithms being functions.
		If that’s not enough, in some cases, parameters were removed, making overloads even without function objects difficult.
		Effectively being a source for errors.
		
		Why not provide additional overloads? See section 3.10

**********/

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {
    const std::vector<int>  nums_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    {
        std::cout << "vector size using ranges: " << std::ranges::size(nums_vec) << '\n';
        std::cout << "check if vector is empty using ranges: " << std::boolalpha << std::ranges::empty(nums_vec) << '\n';
    }
    
    {
        auto res = nums_vec | 
            std::views::filter([](const int val) { return not (val & 1);}) |
            std::views::transform([](const int val) { return (val * 2); });

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

    {
        auto fview = std::ranges::filter_view(nums_vec, [](const int val) { return not (val & 1);});
        auto res = std::ranges::transform_view(fview, [](const int val) { return (val * 2); });

        for(const auto & elem: res) {
            std::cout << elem << ',';
        }
        std::cout << '\n';
    }

	return 0;
}

/*****
    END OF FILE
**********/

