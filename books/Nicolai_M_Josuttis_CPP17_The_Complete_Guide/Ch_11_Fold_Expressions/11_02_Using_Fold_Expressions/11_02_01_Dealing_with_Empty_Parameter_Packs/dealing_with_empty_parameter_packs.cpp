/*********

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


11.2.1 Dealing with Empty Parameter Packs
	For empty parameter pack, the following rules apply:
	If operator && is used, the value is true.
	If operator || is used, the value is false.
	If the comma operator is used, the value is void().
	For all other operators the call is ill-formed.
	For all other cases (and in general) you can add an initial value.
	
	Given a parameter pack args, an initial value value and an operator op, C++17 also allows us to write either
	• either a binary left fold
	( value op ... op args )	which expands to	(((value op arg1) op arg2) op arg3) op . . .
	• or a binary right fold
	( args op ... op value )	which expands to	arg1 op (arg2 op . . . (argN op value)))
	The operator op has to be the same on both sides of the ellipsis.

	Also, the first operand might be special, such as in this example:
	template<typename... T>
	void print (const T&... args) {
		(std::cout << ... << args) << '\n';
		std::cout << (args << ... << '\n');		// might not compile or even do something unexpected
	}
	Here, it is important that the first call is the output of the first passed argument to print(), which returns the stream to perform the other output calls. Other implementations might not compile or even do something unexpected.

***************************/

#include <iostream>
#include <string>
#include <utility>

template<typename ... T>
auto leftFoldSum(T ... args) {
    return (... + args);
}

template<typename ... T>
auto rightFoldSum(T ... args) {
    return (args + ...);
}

template<typename ... T>
auto andFoldExpression(T ... args) {
    auto res = (... && args);
    return res;
}

template<typename ... T>
auto orFoldExpression(T ... args) {
    auto res = (... || args);
    return res;
}

template<typename ... T>
auto commaFoldExpression(T ... args) {
    auto res = (... , args);
    return res;
}

template<typename T>
auto spaceBefore(const T & arg) {
    std::clog << ' ';
    return arg;
}

template<typename ... T>
auto display(T ... args) {
    std::clog << R"((std::clog << ... << args) << '\n';)" << '\n';
    (std::clog << ... << args) << '\n';
    
    //std::clog << R"(std::clog << ( args << ... << '\n');)" << '\n';
    //std::clog << ( args << ... << '\n');    // print(1) will compile but print the value 1 left shifted by the value of '\n', which usually is 10, so that the resulting output is 1024

    std::clog << R"((std::clog << ... << spaceBefore(args)) << '\n';)" << '\n';
    (std::clog << ... << spaceBefore(args)) << '\n';


    auto localSpaceBefore = [](const auto & arg) -> decltype(auto) { // decltype(auto) or const auto & to avoid unnecessary copy
        std::clog << ' ';
        return arg;
    };
    std::clog << R"((std::clog << ... << localSpaceBefore(args)) << '\n';)" << '\n';
    (std::clog << ... << localSpaceBefore(args)) << '\n';

    std::clog << R"((std::clog << ... << <in_place_lambda>(args)) << '\n';)" << '\n';
    (std::clog << ... << [](const auto & arg) -> const auto & { // decltype(auto) or const auto & to avoid unnecessary copy
        std::clog << ' ';
        return arg;
    }(args)) << '\n';

    std::clog << R"((... , lambdaWithSpaceAndArgs(args));)" << '\n';
    auto lambdaWithSpaceAndArgs = [](const auto & arg) { 
        std::clog << arg << ' ';
    };
    (... , lambdaWithSpaceAndArgs(args));
    std::clog << '\n';

}

int main() {

    {
        std::clog << "=== Dealing with Empty Parameter Packs\n";
        std::clog << andFoldExpression() << '\n';
        std::clog << orFoldExpression() << '\n';
        //std::clog << commaFoldExpression() << '\n'; // error: 'void res' has incomplete type
        //std::clog << leftFoldSum() << '\n'; // error: fold of empty expansion over operator+
        //std::clog << rightFoldSum() << '\n';    // error: fold of empty expansion over operator+

        display(1);
        display(1, 2.3, 'A', "sample string");
    }

    return 0;
}

/******
    END OF FILE
********/


