/*****

References

    episode https://www.youtube.com/watch?v=QeWdhHyBBv0
    https://en.cppreference.com/w/cpp/ranges/concat_view

    concat_view presents a view factory that takes an arbitrary number of ranges as an argument list, 
    and provides a view that starts at the first element of the first range, 
    ends at the last element of the last range, 
    with all range elements sequenced in between respectively 
    in the order given in the arguments, effectively concatenating, 
    or chaining together the argument ranges

**********/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <ranges>

int main() {

    std::array      arr{1,2,3,4,5};
    std::vector     vec{11.2, 12.3, 13.4, 14.5, 15.6, 16.7};
    //std::list       lst{"string-1", "string-2", "string-3"};
    std::list       lst{21.1f, 22.2f, 23.3f};

    for(const auto & elem : std::views::concat(arr, vec, lst)) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    return 0;
}

/*****
    END OF FILE
**********/

