/*****

ep427_Simple_Generators_Without_Coroutines

    This example demonstrates about writing generators using lambda

    For more info visit
    episode: https://www.youtube.com/watch?v=F37h3FuA8kM

**********/

#include <iostream>
#include <utility>
#include <ranges>

auto generator(auto func) {
    return std::views::iota(0) | std::views::transform(func);
}

int main() {

    auto fib = [i = 0, j = 1] (auto ) mutable {
        return i = std::exchange(j, i+j);
    };

    /*
    for(const auto val : fib | std::views::take(20)) {
        std::cout << val << ' ';
    }
    */

    for(const auto val : generator(fib) | std::views::take(20)) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

	return 0;
}

/*****
    END OF FILE
**********/


