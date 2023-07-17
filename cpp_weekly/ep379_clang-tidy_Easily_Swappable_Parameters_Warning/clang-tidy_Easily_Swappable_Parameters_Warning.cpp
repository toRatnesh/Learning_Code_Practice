/**********
    
    This example demonstrates about clang-tidy's "Easily Swappable Parameters" Warning

    For more info visit
    https://www.youtube.com/watch?v=Zq4yYPG7Erc

    Code
	https://godbolt.org/z/ThsKffse6

**************/

//#include <iostream>
#include <algorithm>

int clamp(int min, int max, int value) {
    //return std::max(min, std::min(max, value));
}

// improvement: define new types
enum min_t : int;
enum max_t : int;

int clamp_improved(min_t min, max_t max, int value) {
    //return std::max(min, std::min(max, value));
}

struct range_t {
    int min;
    int max;
};

// improvement: define new types which keeps thing together and is less error prone
int clamp_improved_02(range_t range_v, int value) {
    return std::max(range_v.min, std::min(range_v.max, value));
}

int main() {
/*
    {
        int min=3, max=4, value=8;
        std::cout << "clamp(3, 4, 8): " << clamp(min, max, value) << '\n';
    }
    {
        min_t min=3; max_t max=4; int value=8;
        std::cout << "clamp_improved(3, 4, 8): " << clamp_improved(min, max, value) << '\n';
    }
    {
        range_t range_v{3,4}; int value=8;
        std::cout << "clamp_improved_02(range_t{3, 4}, 8): " << clamp_improved_02(range_v, 8) << '\n';
    }
*/
    return 0;
}

/**********
    END OF FILE
**************/



