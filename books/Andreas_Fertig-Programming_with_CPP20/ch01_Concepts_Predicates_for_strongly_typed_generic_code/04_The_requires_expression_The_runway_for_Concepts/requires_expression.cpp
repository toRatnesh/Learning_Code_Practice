/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.4 The requires-expression: The runway for Concepts

For better add operation, Let's consider:

A. The type used in Args must have same type
B. add should be called with two or more parameters
C. The type used in Args must support the + operation
D. The operation + should be noexcept, since Add itself is noexcept.
E. The return type of operation + should match that of Args.


Following is how a requires-expression looks

requires(
    T t, U u // Parameter list of the requires-expression 
    ) 
{
	// One or multiple requirements
	// Body of the requires-expression
}

Read it like a constructor of type requires. You can also see it as a function without a return type. 
After the name requires, we have the optional parameter list. Like in a regular function, this parameter list can be empty or can have entries. 
A requires-expression is only used at compile-time to evaluate the different requirements it brings. It never enters our binary.
The parameters we can define in the parameter list of a requires-expression can consist of any type that is available.

We are totally free when it comes to the qualifiers of these types.
We can say that a requires-expression takes a const T& or a const T*.

The body must contain at least one requirement.

A requires-clause (C3, C5 / section 1.3) is a boolean expression. A requires-expression is more complicated.

**********/

#include <iostream>
#include <type_traits>

template <typename ... T>
auto 
x_add(T ... args) {
    return (... + args);
}

// helpers
template<typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
	struct first_arg {
	using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

/* c++17 code
Explanation : 
line with std::enable_if_t very hard to read and understand

The first part, or argument, is the condition. Here we pass are_same_v. 
Should this condition be true, the next parameter gets enabled, which is first_arg_t.
This then becomes the return type of safe_add_cpp17.
*/
template <typename ... T>
std::enable_if_t<are_same_v<T...>, first_arg_t<T...>> 
safe_add_cpp17(T ... args) {
    return (... + args);
}

// using static_assert
template <typename ... T>
auto static_assert_add(T ... args) {

    // this will not prevent instantiation of template    
    static_assert(are_same_v<T...>);

    return (... + args);
}


// using c++20 concept
// concept_add_cpp20 requires that are_same_v is true.
template <typename ... T>
requires(are_same_v<T...>)
auto concept_add_cpp20(T ... args) {
    return (... + args);
}

template<typename ... Args>
concept my_add_requirements = requires(Args... args)
{
	(... + args);                       // SR
	requires are_same_v<Args...>;       // NR
	requires sizeof...(Args) > 1;       // NR
    { (... + args) } noexcept;
    { (... + args) } -> std::same_as<first_arg_t<Args...>>;
};

template<typename ... Args>
requires(my_add_requirements<Args ...>)
auto multi_concept_add(Args&&... args)
{
	return (... + args);
}

int main() {
    {
        std::cout << "=== Using generic template ===\n";
        const int res1 = x_add(2, 3, 4, 5);
        std::cout << "x_add(2, 3, 4, 5) : " << res1 << '\n';

        // this should not compile, to prevent Implicit conversions which might cause loss of precision
        const int res2 = x_add(2, 3, 4, 5.99);
        std::cout << "x_add(2, 3, 4, 5.99) : " << res2 << '\n';
    }

    {
        std::cout << "=== Using generic template with SFINAE ===\n";
        const int res1 = safe_add_cpp17(2, 3, 4, 5);
        std::cout << "safe_add_cpp17(2, 3, 4, 5) : " << res1 << '\n';

        // Clang CE: note: candidate template ignored: requirement 'are_same_v<int, int, int, double>' was not satisfied [with T = <int, int, int, double>]
        //const int res2 = safe_add_cpp17(2, 3, 4, 5.99);
        //std::cout << "safe_add_cpp17(2, 3, 4, 5.99) : " << res2 << '\n';
    }

    {
        std::cout << "=== Using generic template ===\n";
        const int res1 = static_assert_add(2, 3, 4, 5);
        std::cout << "static_assert_add(2, 3, 4, 5) : " << res1 << '\n';

        // Clang CE: error: static assertion failed due to requirement 'are_same_v<int, int, int, double>'
        //const int res2 = static_assert_add(2, 3, 4, 5.99);
        //std::cout << "static_assert_add(2, 3, 4, 5.99) : " << res2 << '\n';
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


    {
        std::cout << "=== Using c++20 concept with multiple requires ===\n";
        const int res1 = multi_concept_add(2, 3, 4, 5);
        std::cout << "multi_concept_add(2, 3, 4, 5) : " << res1 << '\n';

        // candidate template ignored: constraints not satisfied [with Args = <int, int, int, double>]
        // const int res2 = multi_concept_add(2, 3, 4, 5.99);
        
        // candidate template ignored: constraints not satisfied [with Args = <int>]
        // because 'sizeof...(Args) > 1' (1 > 1) evaluated to false
        // const int res3 = multi_concept_add(2);
    }

    return 0; 
}

/*****
    END OF FILE
**********/

