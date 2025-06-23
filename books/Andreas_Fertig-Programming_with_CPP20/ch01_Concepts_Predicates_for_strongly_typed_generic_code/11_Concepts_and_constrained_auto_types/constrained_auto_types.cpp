/*****

References
    Programming with C++20 | Andreas Fertig

    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/language/requires

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.11 Concepts and constrained auto types

1.11.1 Constrained auto variables

we could prefix auto with a concept to constrain auto variables in C++20
Constrained placeholder types allow us to limit the type and 
	its properties without the need to specify an exact type.

1.11.2 Constrained auto returntype

Annotating an return-type has the same auto benefit as for variables, 
or instead of typename, a user can see or lookup the auto interface definition.

**********/

#include <iostream>
#include <vector>

std::integral auto get_size(const auto & container) {
    return container.size();
}


int main() {
    
    std::vector<int> avec{1, 2, 3, 4, 5};
    
    [[maybe_unused]] const std::integral auto vsize1 = avec.size();
    
    [[maybe_unused]] const std::integral auto vsize2 = get_size(avec);

    return 0; 
}

/*****
    END OF FILE
**********/


