/**********
  This example demonstrates about C++ CRTP.

CRTP:
The Curiously Recurring Template Pattern is an idiom in which a class X derives from a class template Y, taking a template parameter Z, where Y is instantiated with Z=X.
CRTP may be used to implement "compile-time polymorphism", when a base class exposes an interface, and derived classes implement such interface.

For more info visit:
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
https://en.cppreference.com/w/cpp/language/crtp

 ***********/

#include <iostream>

template<typename T>
struct B {
    void fun() { static_cast<T &>(*this).fun(); }
};

struct D1 : public B<D1>
{
    void fun() { std::puts("D1::fun()"); }
};

struct D2 : public B<D2>
{
    void fun() { std::puts("D2::fun()"); }
};

int main() {
    B<D1> b1; b1.fun();
    B<D2> b2; b2.fun();
    std::puts("");

    D1 d1; d1.fun();
    D2 d2; d2.fun();

    return 0;
}

/*****
  END OF FILE
 ****/
