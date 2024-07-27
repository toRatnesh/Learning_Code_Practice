/*****

ep423_Complete_Guide_to_Attributes_Through_cpp23

References:
episode     https://www.youtube.com/watch?v=BpulWncdn9Y
https://en.cppreference.com/w/cpp/language/attributes


C++11
[[noreturn]]			indicates that the function does not return
[[carries_dependency]]	indicates that dependency chain in release-consume std::memory_order propagates in and out of the function

C++14
[[deprecated]]
[[deprecated("reason")]]	indicates that the use of the name or entity declared with this attribute is allowed, but discouraged for some reason

C++17
[[fallthrough]]		indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fall-through
[[maybe_unused]]	suppresses compiler warnings on unused entities, if any
[[nodiscard]]
[[nodiscard("reason")]](C++20)	encourages the compiler to issue a warning if the return value is discarded

C++20
[[likely]]
[[unlikely]]			indicates that the compiler should optimize for the case where a path of execution through a statement is more or less likely than any other path of execution
[[no_unique_address]]	indicates that a non-static data member need not have an address distinct from all other non-static data members of its class

C++23
[[assume(expression)]]	specifies that the expression will always evaluate to true at a given point

**********/

#include <cstdint>
#include <print>
#include <exception>

//C++11
//[[noreturn]]			indicates that the function does not return
//[[carries_dependency]]	indicates that dependency chain in release-consume std::memory_order propagates in and out of the function

[[noreturn]] void noreturn_cpp11(const int val) {
    // behavior is undefined if called with val >= 0
    if(val < 0) 
    {
        throw std::runtime_error("Value is negative");
    }
}

//For [[carries_dependency]] example visit
// https://en.cppreference.com/w/cpp/language/attributes/carries_dependency

//C++14
//[[deprecated]]
//[[deprecated("reason")]]	indicates that the use of the name or entity declared with this attribute is allowed, but discouraged for some reason

[[deprecated("use version()")]] 
std::string deprecated_cpp14() {
    return std::string{"1.0.0"};
}


//C++17
//[[fallthrough]]		indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fall-through
//[[maybe_unused]]	suppresses compiler warnings on unused entities, if any
//[[nodiscard]]
//[[nodiscard("reason")]](C++20)	encourages the compiler to issue a warning if the return value is discarded

int fallthrough_cpp17(const int val) {
    int retval = 0;
    switch(val) {
        case 0:
        case 1:
        case 2:
        case 3:
            retval = 1;
            [[fallthrough]];
        case 4:
        case 5:
        case 6:
        case 7:
            retval = 0;   
    }
    retval = -1;
    return retval;
}

[[nodiscard("use instance to access member")]] 
std::string & getInstance() {
    static std::string sinstance;
    return sinstance;
}

//C++20
//[[likely]]
//[[unlikely]]			indicates that the compiler should optimize for the case where a path of execution through a statement is more or less likely than any other path of execution
//[[no_unique_address]]	indicates that a non-static data member need not have an address distinct from all other non-static data members of its class

int likely_cpp20(const int * iptr, const bool release) {

    if(nullptr != iptr) {
        std::println("*iptr {}", *iptr);
        if(release) {
            delete iptr; iptr=nullptr;
        } else {
            // do nothing
        }
    } else {
        std::println("iptr is nullptr");
    }

    return 0;
}

//C++23
//[[assume(expression)]]	specifies that the expression will always evaluate to true at a given point

int assume_cpp23(const int value) {
    [[assume(value > 0)]];
    if(value < 0) {
        return -1;
    }
    
    return 0;
}


int main() {

    try{
        noreturn_cpp11(-2);
        noreturn_cpp11(2);      // UB
    }catch(const std::exception & exp) {
        std::println("{}", exp.what());
    }

    std::println("{}", deprecated_cpp14());

    std::println("{}", fallthrough_cpp17(1));
    std::println("{}", fallthrough_cpp17(4));

    getInstance();
    getInstance().append("This will not generate warning");

    [[maybe_unused]] int val = 5;

    {
        {
            int * ival = new int{5};
            likely_cpp20(ival, false);
            delete ival; ival = nullptr;
        }

        {
            int * ival = new int{7};
            likely_cpp20(ival, true);
        }        
    }

    //std::println("{}", assume_cpp23(5));
    //std::println("{}", assume_cpp23(-5));

    return 0;
}

/*****
    END OF FILE
**********/

