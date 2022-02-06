/**************
 *	This example demonstrates the use of std::optional and std::variant in constexpr context.
 *
 * **********************/

#include <iostream>
#include <optional>
#include <variant>

constexpr auto getOptioalValue() {
	std::optional<int> val = 1;
	//val = 3;                    // possible bug (this assignent is not portable)
	return val;
}

constexpr auto getVariantValue() {
	std::variant<int, double> val = 5.7;
	//val = 6.8;  // CE:  error: call to non-'constexpr' function 'std::enable_if_t ...
	return val;
}

int main() {
	constexpr auto res = getOptioalValue();
	std::cout << *res << '\n';

	constexpr auto res_v = getVariantValue();
	std::cout << std::get<double>(res_v) << '\n';

	return 0;
}

/*********
 *	END OF FILE
 * ******/
