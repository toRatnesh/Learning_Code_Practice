/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constraints

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.7 Defining a concept

Elements of a concept

template<typename T, typename U>    // template-head
concept my_concept_name = std::same_as<T, U> && 
                            (std::is_class_v<T> || std::is_enum_v<T>);  // requirements

A concept always starts with a template-head. 
The reason is that concepts are predicates in generic code, which makes them templates.

The template-head of a concept comes with the same power and limitations as that of any other function or class template.
We can use type and non-type template parameters (NTTPs) parameters, class or typename, or a concept to declare a template type parameter.

After the template-head, keyword concept starts the concept and tells the compiler that this is the definition of a concept and not, for example, a variable template.

Keyword concept follows by a concept name.
After the concept name, we see the equal sign followed by requirements.
We assign these requirements to our concept (my_concept_name).
As you can see, these requirements can be put together using boolean algebra.
We can use either concepts or type-traits as requirements.


For example now let's improve the code present in section 1.6 Ad hoc constraints using concept

**********/

#include <iostream>
#include <type_traits>

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
	(... + args);
	requires are_same_v<Args...>;
	requires sizeof...(Args) > 1;
	{ (... + args) } noexcept -> std::same_as<first_arg_t<Args...>>;
}
auto ad_hoc_constraint_add(Args&&... args)
{
	return (... + args);
}

template<typename ... Args>
concept IsAddable = requires(Args... args)
{
	(... + args);                       // SR
	requires are_same_v<Args...>;       // NR
	requires sizeof...(Args) > 1;       // NR
    { (... + args) } noexcept;
    { (... + args) } -> std::same_as<first_arg_t<Args...>>;
};

template<typename ... Args>
requires IsAddable<Args ...>    // more redable and IsAddable is reusable
auto concept_add(Args&&... args)
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
        std::cout << "=== Using c++20 concept  ===\n";
        const int res1 = concept_add(2, 3, 4, 5);
        std::cout << "concept_add(2, 3, 4, 5) : " << res1 << '\n';

        // candidate template ignored: constraints not satisfied [with Args = <int, int, int, double>]
        // const int res2 = concept_add(2, 3, 4, 5.99);
        
        // candidate template ignored: constraints not satisfied [with Args = <int>]
        // because 'sizeof...(Args) > 1' (1 > 1) evaluated to false
        // const int res3 = concept_add(2);
    }

    return 0; 
}

/*****
    END OF FILE
**********/

