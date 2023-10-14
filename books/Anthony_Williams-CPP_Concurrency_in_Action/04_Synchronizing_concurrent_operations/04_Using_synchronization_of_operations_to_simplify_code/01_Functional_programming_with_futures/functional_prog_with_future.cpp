/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/concurrency/promise
    https://en.cppreference.com/w/cpp/experimental/future
    https://en.cppreference.com/w/cpp/experimental/shared_future

4.4 Using synchronization of operations to simplify code
        Rather than sharing data directly between threads, each task can be
provided with the data it needs, and the result can be disseminated to any other
threads that need it through the use of futures.

4.4.1 Functional programming with futures
        Functional programming: result of a function call depends solely on the
parameters to that function and doesn’t depend on any external state A pure
function doesn’t modify any external state either; the effects of the function
are entirely limited to the return value

        Futures makes FP-style concurrency viable in C++; a future can be passed
around between threads to allow the result of one computation to depend on the
result of another, without any explicit access to shared data.

**********/

#include <algorithm>
#include <future>
#include <iostream>
#include <vector>
#include <list>

auto display_coll = [](const auto& coll) {
    for (const auto& elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
};

template <typename T>
std::vector<T> seq_quick_sort(std::vector<T> input) {

    if (input.empty() or (1 == input.size())) {
        return input;
    }

    std::vector<T> result;
    result.insert(result.begin(), *input.begin());

    const T pivot = *result.begin();
    input.erase(input.begin());
    
    auto div_point = std::partition(
        input.begin(), input.end(),
        [pivot = std::move(pivot)](const T& t) { return t < pivot; });

    std::vector<T> lower_part;
    lower_part.insert(lower_part.end(), std::make_move_iterator(input.begin()),
                      std::make_move_iterator(div_point));
    input.erase(input.begin(), div_point);

    auto new_low = seq_quick_sort(std::move(lower_part));
    auto new_high = seq_quick_sort(std::move(input));
    
    result.insert(result.begin(), new_low.begin(), new_low.end());
    result.insert(result.end(), new_high.begin(), new_high.end());

    return result;
}

template <typename T>
std::vector<T> par_quick_sort(std::vector<T> input) {
    if (input.empty() or (1 == input.size())) {
        return input;
    }

    std::vector<T> result;
    result.insert(result.begin(), *input.begin());
    
    const T pivot = *result.begin();
    input.erase(input.begin());

    auto div_point = std::partition(
        input.begin(), input.end(),
        [pivot = std::move(pivot)](const T& t) { return t < pivot; });

    std::vector<T> lower_part;
    lower_part.insert(lower_part.end(), std::make_move_iterator(input.begin()),
                      std::make_move_iterator(div_point));
    input.erase(input.begin(), div_point);

    auto fut_new_low = std::async(par_quick_sort<T>, (std::move(lower_part)));
    auto fut_new_high = std::async(par_quick_sort<T>, (std::move(input)));

    auto new_low = fut_new_low.get();
    auto new_high = fut_new_high.get();

    result.insert(result.begin(), new_low.begin(), new_low.end());
    result.insert(result.end(), new_high.begin(), new_high.end());

    return result;
}

int main() {
    {
        std::vector vec{4, 5, 1, 3, 2, 5};
        auto s_vec = seq_quick_sort(std::move(vec));
        display_coll(s_vec);
    }

    {
        std::vector vec{5, 4, 1, 3, 2, 2};
        auto s_vec = par_quick_sort(std::move(vec));
        display_coll(s_vec);
    }

    return 0;
}

/*****
    END OF FILE
**********/

