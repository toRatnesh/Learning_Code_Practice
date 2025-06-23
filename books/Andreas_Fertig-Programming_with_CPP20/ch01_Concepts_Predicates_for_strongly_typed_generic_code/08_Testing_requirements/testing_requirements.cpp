/*****

References
    Programming with C++20 | Andreas Fertig

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.8 Testing requirements
concepts only live at compile time
check things at compile time with static_assert, no need to check out a testing framework

**********/

#include <iostream>
#include <type_traits>

namespace nonstd {
    template<typename T, typename U>
    concept same_as = std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
}


// A Class template stub to create the different needed properties
template <bool no_except, bool operator_plus, bool valid_return_type>
struct Stub {
    // Operator plus with controlled noexcept can be enabled
    Stub& operator+(const Stub& ) noexcept(no_except)
    requires(operator_plus && valid_return_type)
    {
        return *this;
    }

    // Operator plus with invalid return type
    int operator+(const Stub& ) noexcept(no_except)
    requires(operator_plus && not valid_return_type)
    {
        return {};
    }
};

template<typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
	struct first_arg {
	using type = T;
};

template<typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template<typename ... Args>
concept IsAddable = requires(Args... args)
{
	(... + args);                       // SR
	requires are_same_v<Args...>;       // NR
	requires sizeof...(Args) > 1;       // NR
    { (... + args) } noexcept -> nonstd::same_as<first_arg_t<Args...>>;
};

template<typename ... Args>
requires IsAddable<Args ...>    // more redable and IsAddable is reusable
auto concept_add(Args&&... args)
{
	return (... + args);
}

int main() {

    std::cout << "=== Using c++20 concept  ===\n";
    const int res1 = concept_add(2, 3, 4, 5);
    std::cout << "concept_add(2, 3, 4, 5) : " << res1 << '\n';

    // candidate template ignored: constraints not satisfied [with Args = <int, int, int, double>]
    // const int res2 = concept_add(2, 3, 4, 5.99);
    
    // candidate template ignored: constraints not satisfied [with Args = <int>]
    // because 'sizeof...(Args) > 1' (1 > 1) evaluated to false
    // const int res3 = concept_add(2);

    using ValidClass = Stub<true, true, true>;
    using NoAdd = Stub<true, false, true>;
    using NotNoexcept = Stub<false, true, true>;
    using DifferentReturnType = Stub<true, true, false>;

    static_assert(IsAddable<int, int>);
    static_assert(IsAddable<ValidClass, ValidClass>);

    static_assert(not IsAddable<int, double>);
    static_assert(not IsAddable<int>);
    static_assert(not IsAddable<DifferentReturnType, DifferentReturnType>);

    static_assert(not IsAddable<NotNoexcept, NotNoexcept>);
    static_assert(not IsAddable<NoAdd, NoAdd>);

    return 0; 
}

/*****
    END OF FILE
**********/


