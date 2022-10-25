/**********
    
Reference: 
    The C++ Standard Library Second Edition | Nicolai M. Josuttis
    
This example demonstartes about C++11 Lambda    
    A lambda is a definition of functionality that can be defined inside statements and expressions. Thus, you can use a lambda as an inline function.

Syntax of Lambdas
    [...] {...}
    or
    [...] (...) mutableopt throwSpecopt ->retTypeopt {...}

    Between the [] and the {}, you can specify parameters, mutable, an exception specification, attribute specifiers, and the return type. 
    All of them are optional, but if one of them occurs, () for the parameters are mandatory.

Captures
    Inside the [], you can specify a capture to access data of outer scope that is not passed as an argument:
    [x]		captures x by value
    [&x]	captures x by reference
    [=]		captures all variables (used in the lambda) by value
    [&]		captures all variables (used in the lambda) by reference
    [=, &x]	captures variables like with [=], but x by reference, =x not allowed
    [&, x]	captures variables like with [&], but x by value, &x is not allowed

    With mutable, a lambda becomes stateful even if the state is passed by value. Without mutable, which is the usual case, operator () becomes a constant member function so that you only have read access to objects that were passed by value.

Type of Lambda
    The type of a lambda is an anonymous function object (or functor). To declare objects of that type, you need templates or auto. If you need the type, you can use decltype().
    Alternatively, you can use the std::function<> class template, provided by the C++ standard library, to specify a general type for functional programming. That class template provides the only way to specify the return type of a function returning a lambda.

**********/

#include <iostream>
#include <functional>

std::function<int(int, int)> getLambda() {
    return [](int m, int n){ return m*n;};
}

int main() {

    static int static_val = 5;
    int val = 7;
    int change_val = 3;

    auto simple_lambda = [val]{return static_val + val;};
    std::clog << "simple_lambda() "<< simple_lambda() << '\n';

    auto lambda_with_capture = [val, &change_val] (int newval) { ++change_val; return (val*newval) + change_val; };
    std::clog << "lambda_with_capture(3) " << lambda_with_capture(3) << ", change_val " << change_val << '\n';
    std::clog << "lambda_with_capture(4) " << lambda_with_capture(4) << ", change_val " << change_val << '\n';

    decltype(lambda_with_capture) lambda_like_lambda_with_capture = lambda_with_capture;
    std::clog << "lambda_like_lambda_with_capture(5) " << lambda_like_lambda_with_capture(5) << ", change_val " << change_val << '\n';

    auto lambda_fun = getLambda();
    std::clog << "lambda_fun(5, 6) " << lambda_fun(5, 6) << '\n';

    return 0;
}


/***********
    END OF FILE
*********/
