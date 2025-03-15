/*****

References
    Programming with C++20 | Andreas Fertig

    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/language/requires

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.14 Improved error message

	One other implicit goal of concepts is improving the error messages you get from compiler 
	if you supply an invalid argument for a template.

**********/

#include <iostream>

#include <vector>
#include <list>
#include <algorithm>

template<typename T>
concept has_sorted_method = requires(T t) { t.sort(); };

template<typename T>
concept not_has_sorted_method = not requires(T t) { t.sort(); };

// template<typename T>
template<not_has_sorted_method T>
void printSorted(T cont) {
    std::sort(cont.begin(), cont.end());
    for(const auto & elem : cont) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

template<has_sorted_method T>
void printSorted(T cont) {
    cont.sort();
    for(const auto & elem : cont) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void sortedVector() {
    std::vector lvec{1, 2, 5, 6, 9, 4, 3, 7, 8};
    printSorted(lvec);
}

void sortedList() {
    std::list lst{1, 2, 5, 6, 9, 4, 3, 7, 8};
    printSorted(lst);
}

int main() {
    sortedVector();
    sortedList();
    return 0; 
}

/*****
    END OF FILE
**********/


