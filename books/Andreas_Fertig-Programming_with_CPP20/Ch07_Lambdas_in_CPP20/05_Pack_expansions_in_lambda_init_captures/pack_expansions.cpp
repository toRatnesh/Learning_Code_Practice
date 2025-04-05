/*****

References

    Programming with C++20 | Andreas Fertig


Chapter 7 | Lambdas in C++20: New features

    There are several changes therein to make lambdas even more powerful.

7.5 Pack expansions in lambda init-captures

	By making getNamedLogger a variadic template and letting the lambda capture the parameter pack of getNamedLogger, 
	there is another opportunity to waste resources or to apply perfect forwarding.

	perfect forwarding will save additional allocations.

	C++17 solution
	
	use std::tuple inside getNamedLogger. 
	The lambda uses an init-capture tup to capture a std::tuple which contains the moved origins. 
	Inside this first lambda, another lambda is required B. 
	This second lambda is supplied to std::apply inside our original lambda to expand all the values of the wrapping tuple. 
	In its parameter list _origins, it receives the tuple elements as a pack.

	C++20 allows
	
	Pack expansions in init-captures allow us absolutely perfect forwarding of parameters and captures in case of a lambda.
	No additional distracting elements are required.	

	The only difference is we need to tell the compiler that _origins is a pack.
	To do that, we need to add the ellipsis before the init-capture, making it ... _origins.
	If you remember that init-captures are implicitly auto variables, 
	you can think of this as writing auto... _origins, which is consistent with how we use the ellipsis in other places.

**********/

#include <iostream>
#include <string>

template<typename ...Args>
void logit(Args ... args) {
    ((std::cout << args << ' '), ...) << '\n';   
}

template<typename ...Args>
auto loggerCpp17(Args && ...fargs) {
    return [ltup = std::make_tuple(std::forward<Args>(fargs)...)]
        <typename ...Ts>(Ts && ... largs) 
        {
            std::apply(
                [&](const auto & ...args){
                    logit(args..., std::forward<Ts>(largs)...);
                }, 
                ltup);
        };
}

template<typename ...Args>
auto loggerCpp20(Args && ...fargs) {
    return [... fargs = std::forward<Args>(fargs)]
        <typename ...Ts>(Ts && ... largs) 
        {
            logit(fargs..., std::forward<Ts>(largs)...);
        };
}


auto LOG17 = loggerCpp17("C++17", "Pack", "expansion in lambda using tuple:");
auto LOG20 = loggerCpp20("C++20", "Pack", "expansion in lambda using perfect forwarding:");

int main() {
    
    {   std::cout << "\n";
    
        LOG17("This is a sample log");
        LOG17("This is also a log");
        LOG17("Logging an int value", 598);
        LOG17(234, 56.98);
    }

    
    {   std::cout << " \n";

        LOG20("This is a sample log");
        LOG20("This is also a log");
        LOG20("Logging an int value", 598);
        LOG20(234, 56.98);
    }
    return 0;
}

/*****
    END OF FILE
**********/

