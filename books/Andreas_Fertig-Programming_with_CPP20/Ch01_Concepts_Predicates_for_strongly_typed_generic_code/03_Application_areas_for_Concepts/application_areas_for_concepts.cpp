/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.3 Application areas for Concepts

template<C1 T>
requires C2<T>
C3 auto Fun(C4 auto param) requires C5<T>

==============================================================================================
Type 								When to use
==============================================================================================
C1 type-constraint				Use this when you already know that a template 
								type parameter has a certain constraint. 
								For example, not all types are allowed.
---------------------------------------------------------------------------------------------
C2 requires-clause				Use this when you need to add constraints for 
								multiple template type or non-type template parameters.
								
								In a requires-clause, we can use either concepts or type-traits.
								The expression following the requires must return a boolean value at compile time.
---------------------------------------------------------------------------------------------
C3,C4 auto-constraint			We can also use Concepts to constrain auto variables, which we will see later. 
								A constraint placeholder type works only with Concepts.
								Type-traits are not allowed.
---------------------------------------------------------------------------------------------
C5 trailing requires-clause		Use this for a method in a class template to 
								constrain it based on the class template parameters.
---------------------------------------------------------------------------------------------

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

    return 0; 
}

/*****
    END OF FILE
**********/

