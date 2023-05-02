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

14.2 Variadic Using Declarations for Inheriting Constructors
    You can declare a variadic class template that derives from a 
    base class for each of its passed types

*********************/

#include <iostream>
#include <string>

template<typename T>
class Base {
    T m_bval;
    public:
    ~Base() { std::clog << "~Base()\n"; }
    Base()  { std::clog << "Base()\n"; }
    Base(T val) : m_bval(val) { std::clog << "Base(T val)\n"; }
};

template<typename ... Ts>
class MultiTypeDerived : private Base<Ts> ... {    
    public:
        using Base<Ts>::Base ...;
};

int main() {
    using mt_t = MultiTypeDerived<int, std::string, bool>;
    /* By the new language rules, each initialization calls the corresponding constructor 
    for the matching base class and the default constructor for all other base classes */

    mt_t m1 = 41;
    mt_t m2 = std::string("hello");
    mt_t m3 = true;
    
    return 0;
}

/*******
    END OF FILE
*********/
