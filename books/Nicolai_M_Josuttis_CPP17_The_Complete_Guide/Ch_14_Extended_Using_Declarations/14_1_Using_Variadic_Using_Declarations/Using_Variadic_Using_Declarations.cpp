/********************

References
    C++17 - The Complete Guide | Nicolai M. Josuttis

14. Extended Using Declarations
    Using declarations were extended to allow a comma separated list of 
    declarations, to allow them to be used in a pack expansion

    Before C++17
    using Type1:m1;
    using Type2:m2;
    using Type3:m3;

    After C++17
    using Type1:m1, Type2:m2, Type3:m3

14.1 Using Variadic Using Declarations
    Comma separated using declarations provide the ability to generically 
    derive all operations of the same kind from a variadic list of base classes

*********************/

#include <iostream>
#include <string>

template<typename ... Ts>
struct LambdaOverload : Ts ... {

    /* constrcutor is not allowed because C++17 
    allows aggregate initialization of base class */

    /*
        Without the using declaration, the base classes would have two different 
        overloads of the same member function operator(), which is ambiguous.
    */
    
    /*
    Ts::operator() ...; 
    // error: request for member 'operator()' is ambiguous
    // error: need 'typename' before 'Ts::operator()' because 'Ts' is a dependent scope
    */

    using Ts::operator() ...;
};
// deduction guide
template<typename ... Ts>
LambdaOverload(Ts ...) -> LambdaOverload<Ts ...>;

int main() {

    auto combined_lambda = LambdaOverload{
        [](std::string & s) { s = s+s; },
        [](auto & val)      { val = val * val; }
    };
    
    int val = 7;
    combined_lambda(val);
    std::clog << "val: " << val << '\n';

    std::string msg = "sample string ";
    combined_lambda(msg);
    std::clog << "msg: " << msg << '\n';

    [[maybe_unused]] char carr[] = "char array ";
    //combined_lambda(carr);  // error: invalid operands of types 'char [12]' and 'char [12]' to binary 'operator*'

    return 0;
}

/*******
    END OF FILE
*********/
