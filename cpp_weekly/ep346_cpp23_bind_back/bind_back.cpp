/************

  This example demonstrates about C++23 std::bind_back

  For more info visit
https://en.cppreference.com/w/cpp/utility/functional/bind_front
https://www.youtube.com/watch?v=pDiP2frdMnI

 ***********/

#include <iostream>
#include <functional>
#include <ranges>
#include <utility>
#include <algorithm>

struct Point {
	int x, y;
	void displace(int xd, int yd) { x += xd;  y += yd; }
	Point operator+(Point other) { return Point{x+other.x, y+other.y}; }
	void print() const { std::clog << "x: " << x << ", y: " << y << '\n'; }
};

std::vector<Point> get_vec_of_points() {
	return {{1,2}, {3,4}, {5,6}, {7,8}};
}

int main() {

	Point p1{21, 33};   p1.print();
	Point p2{13, 63};   p2.print();

	auto displace_by_1_2 = std::bind_back(&Point::displace, 1, 2);
	displace_by_1_2(p1);
	displace_by_1_2(p2);
	p1.print();
	p2.print();

	auto displace_by_x_3 = std::bind_back(&Point::displace, 3);
	displace_by_x_3(p1, 3);
	displace_by_x_3(p2, 4);
	p1.print();
	p2.print();

	std::clog << "using rages on points\n";
	auto points = get_vec_of_points();
	std::ranges::for_each(points, std::bind_back(&Point::displace, 5, 10));
	std::ranges::for_each(points, &Point::print);

	for(const auto & data : get_vec_of_points() | std::views::transform(std::bind_back(std::plus<>{}, Point{10, 5})) ) {
		data.print();
	}

	return 0;
}

/********
  END OF FILE
 *******/


