/*****

ep428_cpp23_Coroutine_Support_std_generator

    This example demonstrates about std::generator

    It also compares std::generator with lambda based generator

    For more info visit
    episode: https://www.youtube.com/watch?v=7ZazVQB-RKc
    comparison https://godbolt.org/z/s3o9cWvKo

**********/

#include <iostream>
#include <utility>
#include <ranges>
#include <generator>
#include <print>

#ifdef USE_STD_GENERATOR

std::generator<int> fib_generator() {
    int i = 0;
    int j = 1;
    while(true) {
        co_yield i = std::exchange(j, i+j);
    }
}

#else 

auto generator(auto func) {
    return std::views::iota(0) | std::views::transform(func);
}

#endif

int main() {

#ifdef USE_STD_GENERATOR

    std::println("=== using std::generator ===");
    for(const auto val : fib_generator() | std::views::take(20)) {
        std::print("{} ", val);
    }
    std::println(); 

#else 

    auto fib = [i = 0, j = 1] (auto ) mutable {
        return i = std::exchange(j, i+j);
    };

    /*
    for(const auto val : fib | std::views::take(20)) {
        std::cout << val << ' ';
    }
    */

    std::println("=== using lambda as generator ===");
    for(const auto val : generator(fib) | std::views::take(20)) {
        std::print("{} ", val);
    }
    std::println();

#endif

	return 0;
}

/*****
    END OF FILE
**********/


