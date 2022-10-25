/********
  This example demonstrates about C++17 constexpr if feature

  For more info visit
https://www.youtube.com/watch?v=CmViCSHXToM
https://en.cppreference.com/w/cpp/language/if
https://www.modernescpp.com/index.php/constespr-if
C++ Weekly episode 18

 ***********/

#include <type_traits>

template<typename T>
constexpr T getval(T val) {
	if constexpr(std::is_integral_v<T>) {
		return val * 2;
	} else if constexpr (std::is_floating_point_v<T>) {
		return val * 5;
	} else {
		return val;
	}
}

int main() {
	static_assert(4 == getval(2));
	//static_assert(3 == getval(2));
	static_assert(11.5 == getval(2.3));
	//static_assert(11.8 == getval(2.3));
	static_assert("This a const char array" == getval("This a const char array"));
	//static_assert("This a const char array" == getval("This a char array"));
}

/********
  END OF FILE
 *******/
