/***********
  This example demonstrates how use of 'using namespace' can lead to wrong function call, and why it should be avoided.

  For more nfo visit:
https://isocpp.org/wiki/faq/coding-standards#using-namespace-std
https://abseil.io/tips/153


 *************/

#include <iostream>

namespace ns1 {
    auto fun(double val) { return 2 * val; }
}
using namespace ns1;

namespace ns2 {
    auto fun(int val) { return 3 * val;}
}
using namespace ns2;

int main() {
    std::clog << "ns1::fun(1)   :   " << ns1::fun(1) << '\n';
    std::clog << "ns1::fun(1.52):   " << ns1::fun(1.52) << '\n';

    std::clog << "ns2::fun(1)   :   " << ns2::fun(1) << '\n';
    std::clog << "ns2::fun(1.52):   " << ns2::fun(1.52) << '\n';

    std::clog << "fun(1)    :   " << fun(1) << '\n';        // calls ns2::fun // no warning or error
    std::clog << "fun(1.52) :   " << fun(1.52) << '\n';     // calls ns1::fun // no warning or error

    return 0;
}


/*********
  END OF FILE
 ***********/

