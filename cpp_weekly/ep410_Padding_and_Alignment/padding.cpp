/*****

    alignof()
        Returns a value of type std::size_t

    std::alignment_of
        Provides the member constant value equal to the alignment requirement of the type T, as if obtained by an alignof expression. If T is an array type, returns the alignment requirements of the element type. If T is a reference type, returns the alignment requirements of the type referred to.
        If alignof(T) is not a valid expression, the behavior is undefined.


    For more info visit
    episode https://www.youtube.com/watch?v=E0QhZ6tNoRg
    https://en.cppreference.com/w/cpp/types/alignment_of
    https://en.cppreference.com/w/cpp/language/alignof

**********/

//#include <print>
#include <iostream>

struct S {
    int         i;      // 4
    char        j;      // 1        
    int         k;      // 4
    double      m;      // 8
    char        l;      // 1        
    long long   n;      // 8
};                      // 26

struct U {    
    long long   n;      // 8

    double      m;      // 8

    int         k;      // 4
    int         i;      // 4            

    char        j;      // 1        
    char        l;      // 1    
};

int main() {
/*
    std::println("alignof(char) {}",    alignof(char));
    std::println("alignof(int) {}",     alignof(int));
    std::println("alignof(double) {}",  alignof(double));
    std::println("alignof(long long) {}",    alignof(long long));

    std::println("sizeof(S) {}",     sizeof(S));
    std::println("sizeof(S) {}",     sizeof(U));
*/
    std::cout << "alignof(char) "       << alignof(char) << '\n';
    std::cout << "alignof(int) "        << alignof(int) << '\n';
    std::cout << "alignof(double) "     << alignof(double) << '\n';
    std::cout << "alignof(long long) "  << alignof(long long) << '\n';

    std::cout << "sizeof(S) " << sizeof(S) << '\n';
    std::cout << "sizeof(S) " << sizeof(U) << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


