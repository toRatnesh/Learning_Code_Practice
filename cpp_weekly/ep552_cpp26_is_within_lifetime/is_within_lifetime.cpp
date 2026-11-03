/*****

References:
    episode     https://www.youtube.com/watch?v=EaYvQz8oQkM
    https://en.cppreference.com/cpp/types/is_within_lifetime
    code        https://godbolt.org/z/13nPYK5xs

    std::is_within_lifetime
    
    Determines whether the pointer ptr points to an object that is within its lifetime.
    
    During the evaluation of an expression E as a core constant expression, 
    a call to std::is_within_lifetime is ill-formed unless ptr points to an object
    . that is usable in constant expressions, or
    . whose complete object’s lifetime began within E.

    This example is poor use of std::is_within_lifetime

**********/

#include <iostream>

union rep {
    int ival;
    float fval;
};

/*
consteval auto getActiveValue(const rep & rp) {

    if(std::is_within_lifetime(&rp.ival)) {
        return rp.ival;
    } else {
        return rp.fval;
    }
}
*/

int main() {

    /*
    {
        constexpr rep rp{.ival = 5};       
        static_assert(rp.ival == 5);
        
        constexpr auto val = getActiveValue(rp);
        static_assert(val == 5);
        std::cout << "Value " << val << '\n';
    }

    {
        constexpr rep rp{.fval = 3.2f};  
        static_assert(rp.fval == 3.2f);

        //constexpr auto val = getActiveValue(rp);
        //static_assert(val == 3.2f);
        //std::cout << "Value " << val << '\n';
    }
    */

    int ival{};
    float fval{};

    {
        constexpr rep rp{.ival = 5};
        if(std::is_within_lifetime(&rp.ival)) {
            ival = rp.ival;
        } else {
            fval = rp.fval;
        }

        std::cout << "ival " << ival << " fval " << fval << '\n';          
    }

    ival = 0;
    fval = 0;
    {
        constexpr rep rp{.fval = 3.2f};
        if(std::is_within_lifetime(&rp.ival)) {
            ival = rp.ival;
        } else {
            fval = rp.fval;
        }  

        std::cout << "ival " << ival << " fval " << fval << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/



