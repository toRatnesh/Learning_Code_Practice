/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/constexpr.html

Chapter 12 | Doing (more) things at compiletime

12.3 Less restrictive constexpr function requirements

12.3.1 new / delete: Dynamic allocations during compiletime
    The rule is that all memory that is allocated during compile-time must be released at compile-time as well.

    The following dynamic allocation elements are allowed within a constexprfunction:
        ■ a new-expression;
        ■ a delete-expression;
        ■ a call to an instance of std::allocator<T>::allocate;
        ■ a call to an instance of std::allocator<T>::deallocate;
        ■ construct_at;
        ■ destroy_at.

NOTE:
    A placement-new is not allowed for now.
    You can also not use overloaded new-operators inside your class.
    Only the global new is allowed.

**********/

#include <format>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <vector>


constexpr auto getVal () {

    if(std::is_constant_evaluated()) {
        auto val = new int{5};  
        auto ret = *val;
        delete val; val = nullptr; 
        return ret;
    }

    auto val = new int{7};  
    auto ret = *val;
    delete val; val = nullptr;

    return ret;
    
}


int main(const int , char * argv[]) {

    constexpr char carr[] = "constexpr char array";
    static_assert(sizeof(carr) == 21);

    static_assert(getVal() == 5);
    assert(getVal() == 7);

    return 0; 
}

/*****
    END OF FILE
**********/


