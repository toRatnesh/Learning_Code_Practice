/************

    This example demonstartes about template-template parameters
    
    For more info visit
    episode https://www.youtube.com/watch?v=s6Cub7EFLXo
    https://www.ibm.com/docs/en/zos/2.4.0?topic=only-template-template-arguments-c
    https://www.fluentcpp.com/2021/08/13/how-template-template-parameters-can-simplify-template-classes/
    https://www.modernescpp.com/index.php/types-non-types-and-templates-as-template-parameters

***************/

#include <iostream>
#include <string>
#include <vector>
#include <list>

template<typename T1, typename T2>
struct A {
    T1 x;
    T2 y;
};

template<typename T2>
struct A<std::string, T2> {
    std::string x;
    T2 y;
};

template<template<typename T1, typename T2> typename S>
struct B {
    S<int, int>     m_ii{4, 5};
    S<char, int>    m_ci{'A', 6};
    S<int, char>    m_ic{7, 'B'};
    S<int, double>  m_id{1, 2.34};
    S<std::string, int> m_si{"sample string", 5};
};

template<typename Container>
auto get_data_01() {
    Container con;
    con.push_back(1);
    con.push_back(2);
    return con;
}

template<template<typename T> typename Container>
auto get_data_02() {
    Container<int> con;
    if constexpr(requires {con.reserve(5);}) {
        con.reserve(5);
    }
    con.push_back(1);
    con.push_back(2);
    return con;
}

int main() {
    std::clog << "template template parameters\n";
    B<A> l_b;
    std::clog << l_b.m_ii.x << ' ' << l_b.m_ii.y << '\n';
    std::clog << l_b.m_ci.x << ' ' << l_b.m_ci.y << '\n';
    std::clog << l_b.m_ic.x << ' ' << l_b.m_ic.y << '\n';
    std::clog << l_b.m_id.x << ' ' << l_b.m_id.y << '\n';
    std::clog << l_b.m_si.x << ' ' << l_b.m_si.y << '\n';

    { auto data = get_data_01<std::vector<int>>();  }

    { auto data = get_data_02<std::vector>();       }
    { auto data = get_data_02<std::list>();         }

    return 0;
}

/*****
    END OF FILE
*******/


