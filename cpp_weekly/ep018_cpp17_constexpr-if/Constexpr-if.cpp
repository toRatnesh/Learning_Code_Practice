/********************************
 *
 *	This program demonstrates the use of constexpr if defined in C++17.
 *
 *	NOTE:
 *		constexpr if does not follow the rule of short circuit.
 *
 * *********************************/

#include <iostream>
#include <type_traits>

template <typename T> 
void print_type_info(const T & t) {
	if constexpr(std::is_integral_v<T>) {
		if constexpr(std::is_same_v<bool, T>) {
			std::cout << "Type is bool" << '\n';

		}
		else if constexpr(std::is_same_v<char, T>) {
			std::cout << "Type is char" << '\n';           
		}
		else {
			std::cout << "Type is integeral" << '\n';
		}    
	}
	else if constexpr(std::is_floating_point_v<T>) {
		std::cout << "Type is floating" << '\n';
	}
	else {
		std::cout << "Type is not ingeral or floting" << '\n';
	}

	return;
}

int main() {
	print_type_info(13);
	print_type_info(17.89);
	print_type_info("Learning constexpr-if");

	print_type_info('A');
	print_type_info(true);
	return 0;
}


/*******
 *	END OF FILE
 * *****/
