/*************
  This example demonstrates about a few usage of C++ 20 ranges
  For more info visit:
https://www.youtube.com/watch?v=sZy9XcGHmI4&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=345
https://en.cppreference.com/w/cpp/ranges
https://en.cppreference.com/w/cpp/header/ranges
 ***************/

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

namespace nonstd {
	constexpr std::vector<int> get_data() {
		return std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	}

	// 1. Handy adapter for common algorithms
	constexpr auto range_algo() {
		// auto result = std::all_of(get_data().begin(), get_data().end(), 
		//	[](const auto & elem){return elem < 11;}); // get_data().begin() and
		// get_data().end() returns mismatched iterator pair reuslting in error
		auto result = std::ranges::all_of(get_data(), [](const auto& elem) { return elem < 11;});
		return result;
	}

	// 2. Pipable range view
	constexpr auto range_view() {
		auto result = std::ranges::all_of(
			get_data() | std::ranges::views::drop(2) | std::ranges::views::take(3),
			[](const auto& elem) { return elem < 5; });
		return result;
	}

	// 3. lazy transform has interesting implications
	auto iterate_over_range() {
		auto index_elem = [i = std::size_t{0}]<typename T>(const T & elem) mutable {
			return std::pair<std::size_t, const T &>{i++, elem};
		};

		for(const auto & [index, elem] : get_data() | std::ranges::views::transform(index_elem) | std::ranges::views::take(5)) {
			std::clog << index << ':' << elem << '\n';
		}
	}
}

int main() {
	static_assert(true == nonstd::range_algo());
	static_assert(false == nonstd::range_view());
	nonstd::iterate_over_range();
	return 0;
}

/*************
  END OF FILE
 *************/

