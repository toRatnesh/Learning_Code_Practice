/***********
 *	This example demonstrates the use of in_place_t.
 *
 *	in_place_t:
 *	std::in_place, std::in_place_type, and std::in_place_index are disambiguation tags that can be passed to the constructors of std::optional, std::variant, and std::any to indicate that the contained object should be constructed in-place, and (for the latter two) the type of the object to be constructed.
 *
 *	The corresponding type/type templates std::in_place_t, std::in_place_type_t and std::in_place_index_t can be used in the constructor's parameter list to match the intended tag.
 *
 *	For more info visit:
 *	std::in_place:	https://en.cppreference.com/w/cpp/utility/in_place
 *	 std::optional:	https://en.cppreference.com/w/cpp/utility/optional
 *	 std::variant:	https://en.cppreference.com/w/cpp/utility/variant
 *	 std::any:	https://en.cppreference.com/w/cpp/utility/any
 *
 *	 NOTE:	Creatting in place is better than moving or copying.
 *
 * ************/

#include <iostream>
#include <optional>
#include <vector>
#include <any>

int main() {
	std::vector<int> lvec(10, 7);
	std::optional<std::vector<int>> o1(std::move(lvec));
	std::optional<std::vector<int>> o2(std::vector<int>(10, 3));
	std::optional<std::vector<int>> o3(std::in_place, 10, 13);
	std::optional<std::vector<int>> o4(std::in_place, {11, 22, 33, 44, 55});
	const auto o5 = std::make_optional<std::vector<int>>(10, 13); // make_optional also have in_place version 
	const auto o6 = std::make_optional<std::vector<int>>({11, 22, 33, 44, 55}); // make_optional also have in_place version 

	std::any a1(std::in_place_type_t<std::vector<int>>{}, 10, 13);
	std::any a2(std::in_place_type_t<std::vector<int>>{}, {11, 22, 33, 44, 55});

	if(o5.has_value()) {
		std::cout << "optinal vector size: " << o5.value().size() << '\n';
	}

	if(o6.has_value()) {
		std::cout << "optinal vector size: " << o6.value().size() << '\n';
	}

	return 0;
}

/***********
 *	END OF FILE
 * *********/
