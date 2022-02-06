/*************
  This example demonstrates about std::initializer_list
  std::initializer_list is created with the help of an array

  For more info visit:
  C++ Insights - Episode 20: What's behind a std::initializer_list | https://www.youtube.com/watch?v=oEWPaiqnquY
https://en.cppreference.com/w/cpp/utility/initializer_list

 *************/

#include <iostream>

struct S {
    S() { std::puts("default constructor"); }
    S(const S & other) { std::puts("copy constructor"); }
    S(const S && other) { std::puts("move constructor"); }
    S(const std::initializer_list<S> &) { std::puts("Initializer list constructor"); }
};

int main() {
    /*
       S s;
       S s2(s);
       S s3{s, s2};
       */
    // these are some extra info from twitter and stackoverflow regarding initializer_list
    // https://twitter.com/Cor3ntin/status/1482506920774807552
    // https://stackoverflow.com/questions/70727088/why-cant-i-use-an-arbitrary-nesting-of-braces-to-construct-most-classes

    std::puts("int x{}: ");
    int x{};
    std::cout << x << '\n';

    std::puts("S{}:");
    S{};

    std::puts("S{{}}:");
    S{{}};

    std::puts("S{{{}}}:");
    S{{{}}};

    return 0;
}

/*******
  END OF FILE
 ********/

