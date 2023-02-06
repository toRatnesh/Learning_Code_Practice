/************

    This example demonstrates about 'typename' vs 'class' difference in template

    For more info visit
        Item 42: Understand the two meanings of typename | Effective C++ - Scott Meyers
        https://www.youtube.com/watch?v=86Pa973BW4Y

Item 42: Understand the two meanings of typename | Effective C++ - Scott Meyers
    From C++’s point of view, class and typename mean exactly the same thing when declaring a template parameter.
    C++ doesn’t always view class and typename as equivalent, however. Sometimes you must use typename.

    If the parser encounters a nested dependent name in a template, it assumes that the name is not a type unless you tell it otherwise. By default, nested dependent names are not types.
    General rule is simple: anytime you refer to a nested dependent type name in a template, you must immediately precede it by the word typename.

    Things to Remember
    ✦ When declaring template parameters, class and typename are interchangeable.
    ✦ Use typename to identify nested dependent type names, except in base class lists or as a base class identifier in a member initialization list.

Episode:
    In case of template template parameter 
    Before C++17    we need to use class
    Since  C++17    we can use typename/class

***************/

#include <iostream>
#include <array>

//template<class C>     // this will also work
template<typename C>
void display(const C & container) {
    // Item42: this name is assumed to not be a type
    //C::const_iterator iter(container.begin()); // CE error: need 'typename' before 'C::const_iterator' because 'C' is a dependent scope

    //class C::const_iterator iter(container.begin());    // CE error: 'class C::const_iterator' resolves to 'std::array<int, 5>::const_iterator' {aka 'const int*'}, which is not a class type
    typename C::const_iterator iter(container.begin());

    while(iter != container.end()) {
        std::clog << *iter << ' ';
        ++iter;
    }
    std::clog << '\n';

    return ;
}

// template-template
template<typename T1, typename T2>
struct A {
    T1 x;
    T2 y;
};

template<typename T2>
struct A<int, T2> {
    int x;
    T2 y;
};

//template<template<typename T1, typename T2> class S> // (pre C++17)
//template<template<typename T1, typename T2> typename S> // (pre C++17) warning: ISO C++ forbids typename key in template template parameter; use '-std=c++17' or '-std=gnu++17'
template<template<typename T1, typename T2> typename S>
struct B {
    S<int, int>     m_ii{4, 5};
    S<char, int>    m_ci{'A', 6};
    S<int, char>    m_ic{7, 'B'};
    S<int, double>  m_id{1, 2.34};
};

int main() {
    std::clog << "nested dependent type parameter \n";
    std::array<int, 5> larr{1,2,3,4,5};
    display(larr);

    std::clog << "template template parameter \n";
    B<A> l_b;
    std::clog << l_b.m_ii.x << ' ' << l_b.m_ii.y << '\n';
    std::clog << l_b.m_ci.x << ' ' << l_b.m_ci.y << '\n';
    std::clog << l_b.m_ic.x << ' ' << l_b.m_ic.y << '\n';
    std::clog << l_b.m_id.x << ' ' << l_b.m_id.y << '\n';

    return 0;
}

/*****
    END OF FILE
*******/



