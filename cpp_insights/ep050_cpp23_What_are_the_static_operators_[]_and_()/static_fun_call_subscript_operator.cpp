/*****

ep050_cpp23_What_are_the_static_operators_[]_and_() 

References
episode https://www.youtube.com/watch?v=hbg1HwUUmw4

This example demonstrates about C++23 stattic operator () and []
When used this does not reuqire this pointer

These are useful in case of lambda without capture or when you write your own callale or closure

**********/

#include <print>
#include <vector>
#include <algorithm>

auto is_even = [](const int val) static { return (0 == (val %2)); };

void display_vec(const auto & vec) {
    for(const auto & elem: vec) {
        std::print("{} ", elem);
    }
    std::println();
}

int main() {

    const std::size_t   vec_size{10};
    std::vector<int>    ivec{vec_size};

    for(std::size_t i = 0; i < vec_size; ++i) {
        ivec.push_back(static_cast<int>(i));
    }

    display_vec(ivec);
    ivec.erase(std::remove_if(ivec.begin(), ivec.end(), is_even), ivec.end());
    display_vec(ivec);

    return 0;
}

/*****
    END OF FILE
**********/

