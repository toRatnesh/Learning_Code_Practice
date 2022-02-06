/***************
 *	This exmample demonstrates the improvement of visitor which was demonstartes in episode 49
 *	ep049_cpp17_Why_Inherit_From_Lambdas.
 *
 *	This example uses c++17 aggregate initialization feature.
 *	https://en.cppreference.com/w/cpp/language/aggregate_initialization
 *
 * **************/

#include <iostream>
#include <utility>
#include <variant>
#include <type_traits>

template<typename ... Base>
struct Visitor : Base ... 
{
	/*  	C++17 allow aggregate initializaton of base class so this construtor is not required
		template<typename ... T>
		constexpr Visitor(T&& ... targ) noexcept(
		(std::is_nothrow_move_constructible_v<Base> && ...)
		): Base{std::forward<T>(targ)} ...
		{    }
		*/

	// making base class opertor()() visibe in inherited class
	using Base::operator() ...;
};

template<typename ... T>
Visitor(T ... targ) -> Visitor<T ... >; // decay_t is no more because we are taking params by value

int main()
{
	// now we are able to initialize constexpr visitor
	constexpr Visitor lvisitor{
		[](int i) -> int { return i + 1; },
			[](double d) -> int { return d + 1.1; }
	};

	constexpr auto val = std::variant<int, double>{6.9};
	constexpr auto res = std::visit(lvisitor, val);
	std::cout << res << '\n';

	return 0;
}

/*******
 *	END OF FILE
 * ********/
