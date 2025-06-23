/*****

References
    Programming with C++20 | Andreas Fertig

    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/language/requires

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.10 Using a constexpr function in a concept

We can use result of a constexpr function as a part of a requirement in a concept, 
but only if the function does not use a parameter created in a requires expression or or if we play tricks.

**********/

#include <iostream>
#include <array>

constexpr auto GetSize(const auto & t = {}) {
    return t.size();   
}

template<typename T, size_t N>
concept SizeCheck = (GetSize<T>() == N);


/*
    The compiler is smart enough to deduce the type of the function’s parameter 
    and passes it as the first argument to the concept SizeCheck.
*/
void useOnlySingleElement(const SizeCheck<1> auto &  ) {
}

int main() {

    std::array<int, 1> arr{0};
    useOnlySingleElement(arr);

    return 0; 
}

/*****
    END OF FILE
**********/


