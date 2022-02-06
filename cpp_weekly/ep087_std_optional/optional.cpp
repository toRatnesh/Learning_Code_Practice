/****************
 * 	std::optional
 * 	The class template std::optional manages an optional contained value, i.e. a value that may or may not be present.
 *
 * 	For more detail check:
 * 	https://en.cppreference.com/w/cpp/utility/optional	
 *
 * ******************/

#include <iostream>
#include <string>
#include <optional>

int main() {
	std::optional<std::string> o1("This is an optional string");
	std::cout << o1.value() << '\n';

	std::optional<std::string> o2;
	std::cout << o2.value_or("Optional value is empty") << '\n';

	auto o3 = std::make_optional(5);
	std::cout << o3.value_or(11) << '\n';

	return 0;
}


/*******
 *	END OF FILE
 * ******/
