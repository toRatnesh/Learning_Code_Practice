/****************
CNTTP:  Class Non-Type Template Parameter

This example demonstrates about c++20 CNTTP feature and how it may be used to pass constexpr parameters to functions.
For more info visit:
Tutorial:   https://www.youtube.com/watch?v=iIizz2bbkiA&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=252
https://en.cppreference.com/w/cpp/language/template_parameters

 ***************/

#include <array>

struct test {
    int x;
    int y;
    int z;
};

constexpr auto use_test(const test & t) {
    std::array<int, t.x> larr{};
    return larr;
}

// use of CNTTP since c++20
//template<test t>
template<auto t>    // auto since c++17
constexpr auto use_test2() {
    std::array<int, t.x> larr{};
    return larr;
}

int main () {
    constexpr test t{5,6,7};
    use_test(t);
    use_test2<t>();
    return 0;
}


/******
  END OF FILE
 *******/
