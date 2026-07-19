/*****

References

	episode https://www.youtube.com/watch?v=_wIj799nLOc
    https://en.cppreference.com/cpp/language/operators#Array_subscript_operator
    https://www.sandordargo.com/blog/2023/08/09/cpp23-multidimensional-subscription-operator

    code https://godbolt.org/z/Pjnxzr7er
    
    Since c++23 operator[] can take any number of subscripts.
    For example, an operator[] of a 3D array class declared as 
    T& operator[](std::size_t x, std::size_t y, std::size_t z); 
    can directly access the elements.

**********/

#include <print>
#include <string>
#include <array>

int main() {


    std::array<std::array<std::array<std::string, 5>, 4>, 2> larr{{
        {{
            {"s-111", "s-112", "s-113", "s-114", "s-115"},
            {"s-121", "s-122", "s-123", "s-124", "s-125"},
            {"s-131", "s-132", "s-133", "s-134", "s-135"},
            {"s-141", "s-142", "s-143", "s-144", "s-145"}
        }},
        {{
            {"s-211", "s-212", "s-213", "s-214", "s-215"},
            {"s-221", "s-222", "s-223", "s-224", "s-225"},
            {"s-231", "s-232", "s-233", "s-234", "s-235"},
            {"s-241", "s-242", "s-243", "s-244", "s-245"}
        }}                       
    }};

    std::println("{}", larr[1][2][1]);

    return 0;
}

/*****
    END OF FILE
**********/


