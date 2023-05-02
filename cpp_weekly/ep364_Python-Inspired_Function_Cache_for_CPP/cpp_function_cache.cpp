/*******

This example demonstrates about Python inspired function cache for C++

For more info visit
episode https://www.youtube.com/watch?v=lHnYSkZ7Cis

*****************/

#include <iostream>
#include <tuple>
#include <type_traits>
#include <map>

template<typename Callable, typename ... Params>
auto cache(Callable callable, Params && ... params) {
    using param_set_t = std::tuple<std::remove_cvref_t<Params>...>;
    param_set_t l_key{params ...};

    //using result_type_t = std::remove_cvref_t<std::invoke_result_t<Callable, decltype(params)...>>;
    using result_type_t = decltype(callable(std::forward<Params>(params)...));
    
    static std::map<param_set_t, result_type_t> cached_results;
    //using value_type_t = decltype(cached_results)::value_type;

    result_type_t result;
    if(auto itr = cached_results.find(l_key); 
        itr != cached_results.end()) {
        result = itr->second;
    }
    else {
        auto l_val = callable(std::forward<Params>(params)...);
        auto l_ret = cached_results.emplace(l_key, l_val);
        result = l_ret.first->second;
    }
    return result;
}

int get_square(const int val) {
    return val * val;
}

std::size_t fib(const std::size_t val) {
    if(val < 2) {
        return val;
    }

    return cache(fib, val - 1) + cache(fib, val - 2);
}

int main() {
    std::cout << cache(get_square, 2) << '\n';
    std::cout << cache(fib, 13) << '\n';
    std::cout << cache(fib, 13) << '\n';
    std::cout << cache(fib, 13) << '\n';

    std::cout << cache(fib, 50) << '\n';
    std::cout << cache(fib, 50) << '\n';
    std::cout << cache(fib, 50) << '\n';

    return 0;
}

/*******
    END OF FILE
*****************/


