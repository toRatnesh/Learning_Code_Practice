/***********

References
    Effective Modern C++ | Scott Meyers

Item 33: Use decltype on auto&& parameters to std::forward them
Generic lambda
    C++14 introduced generic lambda that takes auto as parameter type
    For generic lambda operator() is implemented as a template

    When passing a parameter of auto type to another funciton inside lambda body
    Take parameter as universal reference (auto && parm)
    Pass it to function via std::forward (std::forward<decltype(parm)>(parm))  

    std::forward, convention dictates that the type argument be an 
    lvalue reference to indicate an lvalue and a 
    non-reference to indicate an rvalue

    decltype(parm) will produce lvalue reference for an lvalue, this is according to std::forward requirement
    However,
    decltype(parm) will produce rvalue reference for an rvalue, this is not according to std::forward requirement
    But 
    Applying the reference-collapsing rule that an rvalue reference to an rvalue reference becomes a single rvalue reference,
    instantiating std::forward with an rvalue reference type yields the same result as instantiating it with a non-reference type

Variadic lambda
    C++14 lambdas can also be variadic

*************/

#include <iostream>
#include <initializer_list>

class St {
        int m;
    public:
        St(int val) : m(val) { } 
        void display() const {
            std::clog << "value is " << m << '\n';
        }
};

void fun(const St & st) { std::clog <<"const St & st, "; st.display(); }
void fun(St && st) { std::clog << "St && st, "; st.display(); }

void variadic_fun() { return ; }
template<typename Arg, typename ... Args>
void variadic_fun(Arg && arg, Args && ... args) {
    fun(std::forward<Arg>(arg));
    variadic_fun(std::forward<Args>(args)...);
}

template<typename ... Args>
void variadic_fun_02(Args && ... args) {
    std::initializer_list<bool> {(fun(std::forward<Args>(args)), false) ... };
    return;
}


int main() {
    auto lambda = [](auto && parm){ fun(std::forward<decltype(parm)>(parm)); };
    St s(5);
    St cs(6);

    lambda(s);
    lambda(cs);
    lambda(St{7});

    std::clog << "C++14 Variadic Lambda\n";
    {
        auto variadic_lambda = [](auto && ... parms){ variadic_fun(std::forward<decltype(parms)>(parms)...); };
        variadic_lambda(s, cs, St{7});
    }

    {
        auto variadic_lambda = [](auto && ... parms){ variadic_fun_02(std::forward<decltype(parms)>(parms)...); };
        variadic_lambda(s, cs, St{7});
    }

    return 0;
}

/********
    END OF FILE
********/


