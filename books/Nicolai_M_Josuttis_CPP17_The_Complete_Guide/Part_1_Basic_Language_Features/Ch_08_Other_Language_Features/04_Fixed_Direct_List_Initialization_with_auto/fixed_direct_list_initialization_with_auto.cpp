/************
References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

4. Fixed Direct List Initialization with auto
    C++17 has fixed inconsistency of uniform initialization with braces in C++11
    this is a breaking change, compilers that adopt this change usually also adopt this change even in C++11 mode
    fixed in Visual Studio 2015, g++ 5, and clang 3.8.

    copy list initialization (brace initialization with =) still has the behavior initializing always a std::initializer_list<> when auto is used

    recommended way to initialize variables and objects should always be to use direct list initialization (brace initialization without =)

*************/

#include <iostream>
#include <type_traits>

int main() {

    {
        // before c++17 fix this was deduced as std::initializer_list<int>
        std::clog << "direct list initialization (brace initialization without =)\n";
        auto int_val{5};
        static_assert(std::is_same<decltype(int_val), int>::value, "");
        std::clog << "auto int_val{5} typeid(int_val).name(): " << typeid(int_val).name() << '\n';

        // before c++17 fix this was deduced as std::initializer_list<int>
        //auto list_val{1,2,3}; // error: direct-list-initialization of 'auto' requires exactly one element
        //static_assert(std::is_same<decltype(list_val), std::initializer_list<int>>::value, "");
        //std::clog << "auto list_val{1,2,3}    typeid(list_val).name(): " << typeid(list_val).name() << '\n';
    }

    {
        std::clog << "\ncopy list initialization (brace initialization with =)\n";
        // for auto varible this will always deduce std::initializer_list<>
        auto list_val_1 = {5};
        static_assert(std::is_same<decltype(list_val_1), std::initializer_list<int>>::value, "");
        std::clog << "auto list_val_1 = {5}     typeid(list_val_1).name(): " << typeid(list_val_1).name() << '\n';

        auto list_val_2 = {1,2,3};
        static_assert(std::is_same<decltype(list_val_2), std::initializer_list<int>>::value, "");
        std::clog << "auto list_val_2 = {1,2,3} typeid(list_val_2).name(): " << typeid(list_val_2).name() << '\n';
    }

    return 0;
}

/***************
    END OF FILE
*****************/
