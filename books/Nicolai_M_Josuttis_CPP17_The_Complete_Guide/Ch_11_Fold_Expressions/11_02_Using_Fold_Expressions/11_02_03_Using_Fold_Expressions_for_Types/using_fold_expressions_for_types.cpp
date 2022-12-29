/***********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis


11. Fold Expressions

	Since C++17, there is a feature to compute the result of using a binary operator over all the arguments of a parameter pack (with an optional initial value).
	
	Given a parameter pack args and an operator op, C++17 allows us to write
	• a unary left fold
	( ... op args ) expands to		((arg1 op arg2) op arg3) op . . .			// prefer this
	• a unary right fold
	( args op ... ) expands to		arg1 op (arg2 op . . . (argN-1 op argN))

	The parentheses around the return expression are part of the fold expression and can’t be omitted.
	The order of fold expression arguments can differ and matters (and might look a bit counter-intuitive)
	Because in almost all cases evaluation from left to right is the intention, usually, the left fold syntax with the parameter pack at the end should be preferred (unless this doesn’t work).


11.2 Using Fold Expressions
	Given a parameter pack args and an operator op, C++17 allows us to write
	• a unary left fold
	( ... op args ) expands to		((arg1 op arg2) op arg3) op . . .			// prefer this
	• a unary right fold
	( args op ... ) expands to		arg1 op (arg2 op . . . (argN-1 op argN))

	Because in almost all cases evaluation from left to right is the intention, usually, the left fold syntax with the parameter pack at the end should be preferred (unless this doesn’t work).


11.2.3 Using Fold Expressions for Types
	By using type traits we can also use fold expressions to deal with 
    template parameter packs (an arbitrary number of types passed as template parameters).

****************/

#include <iostream>
#include <type_traits>

// check whether passed types are homogeneous:
template<typename T1, typename... TN>
struct IsHomogeneous {
    static constexpr bool value = (std::is_same<T1,TN>::value && ...);
};
// check whether passed arguments have the same type:
template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...) {
    return (std::is_same<T1,TN>::value && ...);
}

int main() {
    IsHomogeneous<int, decltype(42), decltype(1)>   v1;
    std::clog << v1.value << '\n';
    IsHomogeneous<int, decltype(42), decltype(1.3)> v2;
    std::clog << v2.value << '\n';

    std::clog << isHomogeneous(42, 1, 2) << '\n';
    std::clog << isHomogeneous(42, 1, 2.3) << '\n';
    return 0;
}

/********
    END OF FILE
**************/

