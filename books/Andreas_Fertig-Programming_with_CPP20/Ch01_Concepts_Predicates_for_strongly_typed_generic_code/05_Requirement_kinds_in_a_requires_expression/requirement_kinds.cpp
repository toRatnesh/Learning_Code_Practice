/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.


1.5 Requirement kinds in a requires-expression

1. Simple requirement (SR)
2. Nested requirement (NR)
3. Compound requirement (CR)
4. Type requirement (TR)


1.5.1 The simple requirement

	a simple requirement checks for a simple thing, namely whether a certain statement is valid
	For the Add example, 

	requires(Args... args)
	{
		(... + args);	// SR: args provides +
	}


1.5.2 The nested requirement

	A nested requirement can nest all the other requirement types.
	You can see it as a way to start a new requires-clause inside a requires-expression.

	requires(Args... args)
	{
		(... + args);	// SR: args provides +
		requires are_same_v<Args...>;	// NR: All types are the same
		requires sizeof...(Args) > 1;	// NR: Pack contains at least two elements
	}

	The requires in front of each nested requirement is crucial.

	One important remark is that all parameters we define in the optional parameter list of the requires-expression should only appear as unevaluated operands. That means that these optional local parameters can be used in a sizeof or decltype expression. Still, we cannot pass them, for example, to a constexpr function, because even in this case, they would be evaluated.


1.5.3 The compound requirement

	a compound requirement uses curly braces to form a scope or compound statement

	requires(Args... args)
	{
		(... + args);		// SR: args provides +
		requires are_same_v<Args...>;	// NR: All types are the same
		requires sizeof...(Args) > 1;	// NR: Pack contains at least two elements
		// CR: ...+args is noexcept and the return type is the same as the first argument type
		// { (... + args) } noexcept;
		// { (... + args) } -> same_as<first_arg_t<Args...>>;
		{ (... + args) } noexcept -> same_as<first_arg_t<Args...>>;
	}

	Next to the fold expression in the compound statement, we see noexcept
	This tells the compiler to check whether the expression in the curly braces is noexcept

	This trailing return type-like arrow is followed by a concept.
	At this point, we must use a concept. Type-traits won’t work at this place

	================================================================================================================
	Code										Requires expression kind 	Description
	================================================================================================================
	(... + args);								Simple requirement			Asserts that the operation a+b is possible.
	requires are_same_v<Args...>;				Nested requirement			Asserts that all types of the pack 
																			Args are of the same type.
	{ (... + args) } noexcept;					Compound requirement		Asserts that the plus operation is noexcept.
	{ (... + args) } -> same_as<U>;				Compound requirement		Asserts that the return type of the plus 
																			operation as the same as U.
	{ (... + args) } noexcept -> same_as<U>;	Compound requirement		Combination of the former two compound requirements. 
																			Asserts that the return type of the plus operation 
																			as the same as U and the operation is noexcept.
	================================================================================================================


1.5.4 The type requirement

	This type of requirement asserts that a certain type is valid.

	concept containerTypes checks that a given type T provides all the types 
	that allocating containers of the STL in C++ usually provide

	template<typename T>
	concept containerTypes = requires(T t)
	{ 
		//A Testing for various types in T
		typename T::value_type;
		typename T::size_type;
		typename T::allocator_type;
		typename T::iterator;
		typename T::const_iterator;
	};

	a type requirement always starts with typename.
	Should we leave the typename out, we are back at a simple requirement.

**********/

#include <iostream>
#include <type_traits>
#include <map>
#include <vector>

// helpers
template<typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
struct first_arg {
	using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

// ad hoc constraints
template<typename... Args>
requires requires(Args... args)
{
	(... + args);                       // SR
	requires are_same_v<Args...>;       // NR
	requires sizeof...(Args) > 1;       // NR
    // { (... + args) } noexcept;
    // { (... + args) } -> same_as<first_arg_t<Args...>>;	
    { (... + args) } noexcept -> std::same_as<first_arg_t<Args...>>;    // CR
}
auto ad_hoc_constraint_add(Args&&... args)
{
	return (... + args);
}


template<typename T>
concept map_types = requires(T t)
{
    // The type requirement
    typename T::key_type;
    typename T::mapped_type;
    typename T::key_compare;

    typename T::value_type;
    typename T::size_type;
    typename T::allocator_type;
    typename T::iterator;
    typename T::const_iterator;
};

template<typename T>
requires(map_types<T>)
void displayMap(T amap_cont) {
    for(const auto & [k, v] : amap_cont) {
        std::cout << k << ' ' << v << '\n';
    }
    std::cout << '\n';
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
        std::cout << "=== The type requirement ===\n";
        std::map<std::string, std::string> amap{
            {"key-1", "val-1"},
            {"key-2", "val-2"},
            {"key-3", "val-3"},
            {"key-4", "val-4"},
            {"key-5", "val-5"}
        };
        displayMap(amap);

        std::vector<std::string> avec{"val-1", "val-2", "val-3", "val-4", "val-5"};
        // candidate template ignored: constraints not satisfied [with T = std::vector<std::string>]
        // displayMap(avec);
    }

    return 0; 
}

/*****
    END OF FILE
**********/

