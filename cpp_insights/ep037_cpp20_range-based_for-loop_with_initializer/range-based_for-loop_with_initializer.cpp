/******

    This example demonstrates about varible initializer inside for loop since C++20
    For more info visit
    episode https://www.youtube.com/watch?v=1CC9zquwP3k

*************/

#include <iostream>
#include <vector>

int main() {
    std::vector lvec{1,2,3,4,5};
    for(const auto & e : lvec) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    for(int lval = 3; const auto & e : lvec) {
        std::cout << e << ' ';
        if(e == lval) break;
    }
    std::cout << '\n';

    return 0;
}

/**********
    END OF FILE
*************/

