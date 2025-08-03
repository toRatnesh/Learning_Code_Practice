/*****

References:
    episode https://www.youtube.com/watch?v=MvjBJmsbM4g
    https://en.cppreference.com/w/cpp/language/lambda.html
    https://en.cppreference.com/w/cpp/language/lambda.html#Lambda_capture
    https://eel.is/c++draft/expr.prim.lambda.capture

    If an expression potentially references a local entity within a scope in which it is odr-usable ([basic.def.odr]), 
    and the expression would be potentially evaluated if the effect of any enclosing typeid expressions ([expr.typeid]) were ignored, 
    the entity is said to be implicitly captured by each intervening lambda-expression with an associated capture-default 
    that does not explicitly capture it.
    The implicit capture of *this is deprecated when the capture-default is =; see [depr.capture.this].

**********/

#include <iostream>
#include <string>
#include <string_view>
#include <array>

template<typename T>
void display(T val) {
    std::cout << val << '\n';
}

template<typename T>
void display_coll(const T coll) {
    for(auto & elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {

    {
        const int ival  =   17;
        constexpr std::string_view sv_val = "sample string view value";
        constexpr std::array<double, 5> darr = {12.34, 56.78, 91.23, 45.67, 89.01};

        auto lambda = [](){
            
            display(ival);
            display(sv_val);
            
            //display_coll(darr);
            
            return darr;
            
        };
        auto data = lambda();
        display_coll(data);
    
    }

    return 0;
}

/*****
    END OF FILE
**********/

