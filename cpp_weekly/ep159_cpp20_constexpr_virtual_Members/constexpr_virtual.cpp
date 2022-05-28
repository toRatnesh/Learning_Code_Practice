/******************
  This example demonstrates the use of constexpr virtual member allowed since c++20.

  For more info visit:
https://en.cppreference.com/w/cpp/language/constexpr
https://www.cppstories.com/2021/constexpr-virtual/
https://dev.to/pgradot/let-s-try-c-20-virtual-constexpr-functions-1m0e

 * *******************/

#include <iostream>
#include <array>

struct Base {
    constexpr virtual int get_value() const = 0;
};

struct Derived_1:  Base {
    constexpr virtual int get_value() const override {
        //std::puts("Derived_1 get_value");
        return 5;
    }
};

struct Derived_2:  Base {
    constexpr virtual int get_value() const override {
        //std::puts("Derived_2 get_value");
        return 10;
    }
};

constexpr auto get_some_value() {
    const Derived_1 d1;
    const Derived_1 d2;
    const Derived_1 d3;
    const Derived_2 d4;
    const Derived_2 d5;

    const std::array<const Base *, 5> lar{ &d1, &d2, &d3, &d4, &d5 };
    int sum = 0;
    for(const auto * elem : lar) {
        sum += elem->get_value();
    }
    return sum;
} 

int main() {
    constexpr auto lval = get_some_value();
    std::cout << lval << '\n';

    return 0;
}

/********
 *	END OF FILE
 * *******/
