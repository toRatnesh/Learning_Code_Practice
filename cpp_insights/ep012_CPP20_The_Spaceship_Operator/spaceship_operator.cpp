/********
  This example demonstrates about C++20 spaceship operator

  For more info visit:
https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
https://devblogs.microsoft.com/cppblog/simplify-your-code-with-rocket-science-c20s-spaceship-operator/
https://www.modernescpp.com/index.php/c-20-more-details-to-the-spaceship-operator
C++ Weekly episode 175
 *******/

#include <compare>

struct Point_ii {
	int x;
	int y;
	constexpr auto operator<=>(const Point_ii & rhs) const = default;
	constexpr auto operator==(const int rhs) const {
		return ((rhs == x) && (rhs == y));
	}
};

struct Point_if {
	int x;
	float y;
	constexpr auto operator<=>(const Point_if & rhs) const = default;
};

struct Point_fi {
	float x;
	int y;
	constexpr auto operator<=>(const Point_fi & rhs) const = default;
};

int main() {
	constexpr Point_ii point_ii_01 {2,5};
	constexpr Point_ii point_ii_02 {4,5};
	static_assert(point_ii_01 < point_ii_02);
	constexpr Point_ii point_ii_03 {4,4};
	static_assert(point_ii_03 == 4);
	static_assert(4 == point_ii_03);

	constexpr Point_if point_if_01 {6,2.6f};
	constexpr Point_if point_if_02 {4,6.5f};
	static_assert(point_if_01 > point_if_02);

	constexpr Point_fi point_fi_01 {6.4f,2};
	constexpr Point_fi point_fi_02 {4.8f,6};
	static_assert(point_fi_01 > point_fi_02);

	return 0;
}

/********
  END OF FILE  
 ******/
