/**************
    This example demonstrates about inline varibles in C++17

    inline(C++17):
        Since C++17 you can define a variable/object in a header file as inline and if this definition is used by multiple translation units, they all refer to the same unique object.
        You have to ensure that types are complete before you can initialize them. For example, if a struct or class has a static member of its own type, the member can only be inline defined after the type declaration.
        Since C++17 for static data members, constexpr implies inline

        The initializations are performed when the first translation unit that includes the header or contains these definitions gets entered.

*****************/

#include "fun1.hpp"
#include "fun2.hpp"
#include "common.hpp"

int main() {
    commonobj.display();
    int res1 = fun1();
    int res2 = fun2();
    int res3 = common();
    return res1 + res2 + res3 + SomeType::someval.mval + Data::data;
}

/******************
    END OF FILE
*****************/