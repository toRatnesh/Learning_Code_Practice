/*****

    This example demonstrates about C++23 enumerate

    enumerate_view
    enumerate_view is a range adaptor that takes a view and produces a view of tuples. 
    ith element (the tuple) of the resulting sequence holds: 
        the value equal to i, which is a zero-based index of the element of underlying sequence, and 
        the reference to the underlying element.

    enumerate
    The name views::enumerate denotes a RangeAdaptorObject. 
    Given a subexpression e, the expression views::enumerate(e) is expression-equivalent to 
    enumerate_view<views::all_t<decltype((e))>>(e)  for any suitable subexpression e.

    References
        https://en.cppreference.com/w/cpp/ranges/enumerate_view
        episode https://www.youtube.com/watch?v=HuRbLPRh-Nk

**********/

#include <iostream>
#include <vector>
#include <ranges>
#include <string>

int main() {
    std::vector<std::string>    vec{"Learning", "C++23", "ranges", "views", "enumerate"};

    std::cout << "=== accessing elemnets using range based for loop ===\n";
    for(const auto & elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    std::cout << "\n=== accessing elemnets using enumerate views ===\n";
    for(const auto & [index, elem] : vec | std::ranges::views::enumerate) {
        std::cout << "index " << index << ", value " << elem << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/


