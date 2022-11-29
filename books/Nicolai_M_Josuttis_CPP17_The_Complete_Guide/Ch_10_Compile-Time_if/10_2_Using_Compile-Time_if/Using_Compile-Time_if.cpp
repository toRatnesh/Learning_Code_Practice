/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

10. Compile-Time if

10.2	Using Compile-Time if
	In principle, you can use the compile-time if like the run-time if provided the condition is a compile-time expression.
	You can also mix compile-time and run-time if

	NOTE: you cannot use if constexpr outside function bodies. Thus, you can’t use it to replace conditional preprocessor directives.

10.2.1	Caveats for Compile-Time if
	Compile-Time if Impacts the Return Type
		Compile-time if might impact the return type of a function, depending on which branch gets instantiated
		NOTE: For run time if both return statements are taken into account so that the deduction of the return type is ambiguous.

	else Matters Even if then Returns
		You can always skip the else in the run-time if statements.
		This pattern does not apply to compile-time if, because in the second form the return type depends on two return statements instead of one, which can make a difference.
		
		if(std::is_integral_v<T>) {							if(std::is_integral_v<T>) {
			return t*t;												return t*t;
		}								without else		}
		else {							------------>		
			return t+t;					is same				return t+t;
		}													

		if constexpr(std::is_integral_v<T>) {							if constexpr(std::is_integral_v<T>) {
			return t*t;														return t*t;
		}											without else		}
		else {										------------>		
			return t+t;								may be diff			return t+t;
		}			
		
	Short-Circuit Compile-Time Conditions
		Conditions in run-time ifs short-circuit (evaluating conditions with && only until the first false and conditions with || only until the first true)
		However, the condition for the the compile-time if is always instantiated and needs to be valid as a whole
		If the validity of compile-time conditions depend on earlier compile-time conditions, you have to nest them

10.2.2 Other Compile-Time if Examples
	Perfect Return of a Generic Value
		One application of compile-time if is the perfect forwarding of return values, when they have to
	get processed before they can be returned

	Compile-Time if for Tag Dispatching
		Before C+17, you had to provide an overload set with a separate function for each type you wanted to handle. Now, with compile-time
	if, you can put all the logic together in one function

	Handling of Different Types
		handling of different types in a generic lambda as in std::variant<> visitors

*********************/

#include <iostream>
#include <string>

template<typename T>
auto compiletime_no_short_circuit(T t) {
    if constexpr (std::is_integral_v<T> && T{} != 5) { 
        return t*t;
    }
    else {
        return t;
    }
}

template<typename T>
auto compiletime_short_circuit(T t) {
    if constexpr (std::is_integral_v<T>) {
        if constexpr (T{} != 5) { 
            return t*t;
        }
    }
    else {
        return t;
    }
}

int main() {

    // Short-Circuit Compile-Time Conditions
    std::clog << compiletime_no_short_circuit(3) << '\n';
    //std::clog << compiletime_no_short_circuit(std::string("cpp17")) << '\n';  // // error: no match for 'operator!=' (operand types are 'std::__cxx11::basic_string<char>' and 'int')

    std::clog << compiletime_short_circuit(3) << '\n';
    std::clog << compiletime_short_circuit(std::string("cpp17")) << '\n';

    return 0;
}

/********
    END OF FILE
********/
