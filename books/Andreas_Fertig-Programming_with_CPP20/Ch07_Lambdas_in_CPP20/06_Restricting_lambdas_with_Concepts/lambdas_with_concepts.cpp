/*****

References

    Programming with C++20 | Andreas Fertig


Chapter 7 | Lambdas in C++20: New features

    There are several changes therein to make lambdas even more powerful.

7.6 Restricting lambdas with Concepts


	A lambda with a template-head can restrict the template parameters by 
	using a concept instead of either typename or class to declare a parameter. 
	As with templates, the requires-clause can appear after the template-head, the same way as for a regular template. 
	And last but not least, a lambda can have a trailing requires-clause.

	We can either constraint Ts with a type-constraint or use a requires-clause.

**********/

#include <iostream>
#include <string>

template<typename ...Args>
void logit(Args ... args) {
    ((std::cout << args << ' '), ...) << '\n';   
}

template<typename T>
concept not_floating_point = not std::is_floating_point_v<T>;

template<typename ...Args>
auto loggerCpp20(Args && ...fargs) {
    return [... fargs = std::forward<Args>(fargs)]
        //<typename ...Ts> requires(not std::disjunction_v<std::is_floating_point<Ts>...>)  // requires-clause
        <not_floating_point ...Ts>      // type-constraint
        (Ts && ... largs) 
        requires(not std::disjunction_v<std::is_pointer<Args>...>)
        {
            logit(fargs..., std::forward<Ts>(largs)...);
        };
}

auto LOG20 = loggerCpp20("C++20", "Pack", "expansion in lambda using perfect forwarding:");

int main() {

    LOG20("This is a sample log");
    LOG20("This is also a log");
    LOG20("Logging an int value", 598);
    //LOG20(234, 56.98);  error: no matching function for call to object of type '(lambda at <source>:34:12)'

    return 0;
}

/*****
    END OF FILE
**********/

