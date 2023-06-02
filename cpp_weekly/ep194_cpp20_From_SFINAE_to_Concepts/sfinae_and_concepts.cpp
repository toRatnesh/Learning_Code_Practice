/**************
 *	
 *	-------------------------------
 *		VERY IMPORTANT EPISODE
 *
 *		MUST WATCH IT AS EXAMPLE CODE MAY NOT COVER ALL THE THINGS DISCUSSED IN THIS EPISODE
 *	-------------------------------
 *
 *	This example demonstrates about SFINAE and c++20 concepts.
 *
 *	For more info visit:
 *	Tutorial video:	https://www.youtube.com/watch?v=dR64GQb4AGo&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=195
 *	SFINAE:		https://en.cppreference.com/w/cpp/language/sfinae
 *	Concepts:	https://en.cppreference.com/w/cpp/language/constraints 
 *
 *
 * ***********/

#include <iostream>
#include <type_traits>

template<typename Float_t,
	std::enable_if_t<std::is_floating_point_v<Float_t>, bool> = true // pre c++20
	> 
	//requires(std::is_floating_point_v<Float_t>)     // since c++20
	auto add_float(const Float_t p1, const Float_t p2) {
		return p1 + p2;
	}

template<typename T>
concept Float_point_t = std::is_floating_point_v<T>;

template<Float_point_t Float_t>
auto add_float_ver2(const Float_t p1, const Float_t p2) {
	return p1 + p2;
}

auto add_float_ver3(const Float_point_t auto  p1, const Float_point_t auto p2) {
	return p1 + p2;
}

Float_point_t auto add_float_ver4(const Float_point_t auto  p1, const Float_point_t auto p2) {
	//return int{p1 + p2};  // narrow converison may result in compilation error or warning
	return p1 + p2;
}

auto add_float_ver5(const Float_point_t auto  p1, const Float_point_t auto p2) {
	return int(p1 + p2);
}

int main() {

	//add_float(1.5, 5);
	add_float(1.6, 1.4);
	//add_float(1.6f, 1.4);

	//add_float_ver2(1.5, 5);
	add_float_ver2(1.6, 1.4);
	//add_float_ver2(1.6f, 1.4);

	//add_float_ver3(1.5, 5);
	add_float_ver3(1.6, 1.4);
	add_float_ver3(1.6f, 1.4);      // THIS COMPILES

	//add_float_ver4(1.5, 5);
	add_float_ver4(1.6, 1.4);
	add_float_ver4(1.6f, 1.4);      // THIS COMPILES

	//add_float_ver5(1.5, 5);
	Float_point_t auto val = add_float_ver5(1.6, 1.4);  // CE error: deduced initializer does not satisfy placeholder constraints
	auto val2 = add_float_ver5(1.6f, 1.4);      // THIS COMPILES

	return 0;
}

/******
 *	END O FILE
 * ****/
