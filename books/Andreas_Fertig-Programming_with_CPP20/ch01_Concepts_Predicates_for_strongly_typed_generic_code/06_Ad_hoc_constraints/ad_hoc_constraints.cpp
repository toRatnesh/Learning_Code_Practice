/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.6 Ad hoc constraints

The easiest form is to attach the requires expression built to the requires clause of Add,

template<typename... Args>
requires requires(Args... args)
{
	(... + args);
	requires are_same_v<Args...>;
	requires sizeof...(Args) > 1;
	{ (... + args) } noexcept -> same_as<first_arg_t<Args...>>;
}
auto Add(Args&&... args)
{
	return (... + args);
}

The first line of the requires expression, where it starts with requires, has a requires in front of it. 
So we have requires requires. What we are looking at here is a so-called ad hoc constraint.
The first requires introduced the requires clause, while the second starts the requires expression.
We can, of course, also attach the requires expression to the trailing requires clause.
While an ad hoc constraint is handy, it is also the first sign of a code-smell.

**********/

#include <iostream>
#include <type_traits>

// helpers
template<typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
	struct first_arg {
	using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

// using c++20 concept
// concept_add_cpp20 requires that are_same_v is true.
template <typename ... T>
requires(are_same_v<T...>)
auto concept_add_cpp20(T ... args) {
    return (... + args);
}

// ad hoc constraints
template<typename... Args>
requires requires(Args... args)
{
	(... + args);
	requires are_same_v<Args...>;
	requires sizeof...(Args) > 1;
	{ (... + args) } noexcept -> std::same_as<first_arg_t<Args...>>;
}
auto ad_hoc_constraint_add(Args&&... args)
{
	return (... + args);
}

int main() {

    {
        std::cout << "=== Using ad hoc constraints ===\n";
        const int res1 = ad_hoc_constraint_add(2, 3, 4, 5);
        std::cout << "ad_hoc_constraint_add(2, 3, 4, 5) : " << res1 << '\n';

        // candidate template ignored: constraints not satisfied [with Args = <int, int, int, double>]
        // const int res2 = ad_hoc_constraint_add(2, 3, 4, 5.99);
        
        // candidate template ignored: constraints not satisfied [with Args = <int>]
        // because 'sizeof...(Args) > 1' (1 > 1) evaluated to false
        // const int res3 = ad_hoc_constraint_add(2);
    }

    {
        std::cout << "=== Using c++20 concept requires ===\n";
        const int res1 = concept_add_cpp20(2, 3, 4, 5);
        std::cout << "concept_add_cpp20(2, 3, 4, 5) : " << res1 << '\n';

        // clang CE error: no matching function for call to 'concept_add_cpp20'
        // candidate template ignored: constraints not satisfied [with T = <int, int, int, double>]
        // const int res2 = concept_add_cpp20(2, 3, 4, 5.99);
        //std::cout << "concept_add_cpp20(2, 3, 4, 5.99) : " << res2 << '\n';
    }

    return 0; 
}

/*****
    END OF FILE
**********/

