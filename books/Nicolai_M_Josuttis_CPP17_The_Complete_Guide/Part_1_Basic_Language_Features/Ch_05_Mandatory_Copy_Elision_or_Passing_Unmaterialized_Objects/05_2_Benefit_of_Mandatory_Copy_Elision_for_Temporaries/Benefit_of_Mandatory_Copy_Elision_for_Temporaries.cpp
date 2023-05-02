/***********

References
	C++17 - The Complete Guide | Nicolai M. Josuttis

5. Mandatory Copy Elision or Passing Unmaterialized Objects
    In C++17, former option to eliminate copying temporary objects, when passing or returning them by value, now becomes mandatory.

5.2 Benefit of Mandatory Copy Elision for Temporaries
    Guaranteed better performance when returning a value that is expensive to copy
    May define a factory function that return an object even when copy or move is not allowed
    For classes with explicitly deleted move constructors, you can now return temporaries by value and initialize objects with them

*************/

#include <iostream>
#include <memory>
#include <atomic>

class Test {
    public:
        Test(int) { std::puts("T(int)"); }
        Test(const Test & ) = delete;
        Test(Test && ) = delete;
};
// better performace when returning
Test get_Test() {
    return Test(5);
}

// factory now may crate type which can not be copy or move
template<typename T, typename ... Args_t>
auto create_any(Args_t&& ...args) {
    return T(std::forward<Args_t>(args)...);
}

int main() {
    [[maybe_unused]] Test t1 = 13;
    [[maybe_unused]] Test t = get_Test();

    [[maybe_unused]] auto val = create_any<Test>(5);
    auto unip = create_any<std::unique_ptr<int>>(new int(42));
    auto atmv = create_any<std::atomic<int>>(42);

    return 0;
}

/*******
    END OF FILE
******/


