/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/container/span.html

Chapter 10 | New STL elements

10.4 span: A view of continuous memory

    The class template span describes an object that can refer to a contiguous sequence of objects 
    with the first element of the sequence at position zero. 
    A span can either have a static extent, 
    in which case the number of elements in the sequence is known at compile-time 
    and encoded in the type, or a dynamic extent.

    For a span s, pointers, iterators, and references to elements of s are invalidated when an 
    operation invalidates a pointer in the range [s.data(), s.data() + s.size()).    

    A std::span 
        .   stores only a pointer to the data and the length of the data
        .   the data the std::span refers to must live longer than the span itself (otherwise, we have UB)
        .   is a non-owning container

**********/

#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <span>


void display(const std::span<const int> data) {
    for(const auto & elem: data) {
        std::cout << std::format("{}\n", elem);
    }
}

void display(const std::span<const std::string> data) {
    for(const auto & elem: data) {
        std::cout << std::format("{}\n", elem);
    }
}

int main() {

    {
        const std::vector<std::string> lvec{
            "val-1",
            "val-2",
            "val-3",
            "val-4",
            "val-5",
            "val-6",
        };

        display(lvec);    
    }

    {
        const std::vector<int> lvec{
            1,
            2,
            3,
            4,
            5,
            6,
        };
        std::cout << '\n';
        display(lvec);    
    }

	return 0;
}

/*****
    END OF FILE
**********/

