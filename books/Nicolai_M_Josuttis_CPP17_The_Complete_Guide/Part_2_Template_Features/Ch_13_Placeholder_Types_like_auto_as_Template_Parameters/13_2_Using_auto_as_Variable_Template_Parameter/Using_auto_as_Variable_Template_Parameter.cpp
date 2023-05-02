/********************

References:
        C++17 - The Complete Guide | Nicolai M. Josuttis

13. Placeholder Types like auto as Template Parameters

13.2 Using auto as Variable Template Parameter

    auto can be used as template parameters with variable templates
    each translation unit using that varible share the same global object

    declare a constant variable of an arbitrary type deduced from its initial value

*********************/

#include <iostream>
#include <type_traits>

#include "common.h"

int main() {
    
    {
        std::clog << "=== auto as Variable Template Parameter\n";

        auto & i_arr1 = garr<int, 5>;
        i_arr1[0] = 1;
        i_arr1[2] = 3;
        i_arr1[4] = 5;

        auto & i_arr2 = garr<int, 5u>;
        i_arr2[0] = 11;
        i_arr2[2] = 13;
        i_arr2[4] = 15;

        printArray();

    }

    {
        std::clog << "=== declare a constant variable of an arbitrary type deduced from its initial value\n";
        
        auto v_int      = gval<5>;
        static_assert(std::is_same_v<decltype(v_int), int>);
        static_assert(std::is_same_v<decltype(gval<5>), const int>);

        auto v_char     = gval<'A'>;
        static_assert(std::is_same_v<decltype(v_char), char>);
        static_assert(std::is_same_v<decltype(gval<'A'>), const char>);
        
        auto v_bool     = gval<true>;
        static_assert(std::is_same_v<decltype(v_bool), bool>);
        static_assert(std::is_same_v<decltype(gval<true>), const bool>);
        
        auto v_carr1    = gval<gcarr>;
        static_assert(std::is_same_v<decltype(v_carr1), char *>);
        static_assert( ! std::is_same_v<decltype(gval<gcarr>), const char *>);
        static_assert(std::is_same_v<decltype(gval<gcarr>), char * const>);

        static char lcarr[]    = "local static char array";
        auto v_carr2    = gval<lcarr>;
        static_assert(std::is_same_v<decltype(v_carr2), char *>);
        static_assert( ! std::is_same_v<decltype(gval<lcarr>), const char *>);
        static_assert(std::is_same_v<decltype(gval<lcarr>), char * const>);

        /*  FOOLLWING ARE NOT VALID TEMAPLE NON-TYPE PARAMETERS

        char lcarr[]    = "local char array";
        auto v_carr2    = gval<lcarr>;
        auto v2 = gval<5.3>; // 'double' is not a valid type for a template non-type parameter
        
        */
    }

    return 0;
}

/*******
    END OF FILE
*********/
