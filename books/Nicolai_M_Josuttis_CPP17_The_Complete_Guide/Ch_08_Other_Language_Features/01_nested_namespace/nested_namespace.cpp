/************

References:
        C++17 - The Complete Guide | Nicolai M. Josuttis

1. Nested Namespaces
    C++17 supports nested namespaces like
        namespace nonstd::learning::c++17
    nested namespace is not supported for inline namespace

*************/

#include <iostream>
#include <vector>

namespace cpp17::nested::_namespace {
struct S {
    int m_val;
};
}  // namespace cpp17::nested::_namespace

int main() {
    cpp17::nested::_namespace::S s{5};
    std::clog << "cpp17::nested::_namespace::S s{5}: " << s.m_val << '\n';

    return 0;
}

/***************
    END OF FILE
*****************/
