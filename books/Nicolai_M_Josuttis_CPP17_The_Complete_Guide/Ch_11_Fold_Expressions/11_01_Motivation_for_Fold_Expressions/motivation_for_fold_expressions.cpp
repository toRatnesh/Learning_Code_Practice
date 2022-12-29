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
	
11.1 Motivation for Fold Expressions
	Fold expression avoid the need to recursively instantiate templates to perform an operation on all parameters of a parameter pack.	
	// pre C++17
	template<typename T>
	auto foldSumRec (T arg) { 
		return arg; 
	}
	
	template<typename T1, typename... Ts> 
	auto foldSumRec (T1 arg1, Ts... otherArgs) {
		return arg1 + foldSumRec(otherArgs...);
	}
	
	// post C++17
	template<typename... T>
	auto foldSum (T... args) {
		return (... + args); // arg1 + arg2 + arg3 ...
	}


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

template<typename T>
auto preCPP17FoldExpression(T arg) {   // special case for one argument
    return arg;
}
template<typename First, typename ... T>
auto preCPP17FoldExpression(First arg, T ... args) {
    return arg + preCPP17FoldExpression(args...);
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

int main() {
    {
        std::clog << "=== Fold Expressions\n";
        std::clog << leftFoldSum(11, 10, -1, 5) << '\n';
        std::clog << rightFoldSum(11, 10, -1, 5) << '\n';
        std::clog << leftFoldSum(std::string("Hello "), "world ", "!") <<  '\n';
        //std::clog << rightFoldSum(std::string("Hello "), "world ", "!") <<  '\n'; // error: invalid operands of types 'const char*' and 'const char*' to binary 'operator+'
        std::clog << rightFoldSum("Hello ", "world ",  std::string("!")) << '\n';
        //std::clog << leftFoldSum("Hello ", "world ",  std::string("!")) << '\n';  // error: invalid operands of types 'const char*' and 'const char*' to binary 'operator+'
    }

    {
        std::clog << "=== Motivation for Fold Expressions\n";
        std::clog << preCPP17FoldExpression(11, 10, -1, 5) << '\n';
        //std::clog << preCPP17FoldExpression(std::string("Hello "), "world ", "!") <<  '\n'; // error: invalid operands of types 'const char*' and 'const char*' to binary 'operator+'
    }

    return 0;
}


/******
    END OF FILE
********/


