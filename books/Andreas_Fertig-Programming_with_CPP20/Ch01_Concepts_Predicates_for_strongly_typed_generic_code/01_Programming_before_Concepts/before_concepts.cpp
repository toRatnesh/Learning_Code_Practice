/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.1 Programming before Concepts

Consider the template code to add
    template <typename ... T>
    auto x_add(T ... args) {
        return (... + args);
    }

const int res = x_add(2, 3, 4, 5);		// OK
const int res = x_add(2, 3, 4, 5.99);	// This should not compile

let’s say that we don’t want a static_assert in x_add

for Concepts, we start with an implementation in C++17
for this we need a variadic function template as well as a couple of helpers

check code in example

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

    return 0; 
}

/*****
    END OF FILE
**********/

