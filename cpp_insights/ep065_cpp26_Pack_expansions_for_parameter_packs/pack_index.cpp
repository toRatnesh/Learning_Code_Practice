/*****

References

	episode https://www.youtube.com/watch?v=dfQjKDPXPSk
    https://en.cppreference.com/cpp/language/pack
    https://cppreference.com/cpp/language/pack_indexing

    code https://godbolt.org/z/jWKTs5W6E

    C++26 Pack indexing is a pack expansion of the unexpanded pack 
    followed by an ellipsis and index inside the subscript.
    There are two kinds of pack indexing: 
        1. pack indexing expression 
        2. pack indexing specifier

    Let P be a non-empty pack containing P0, P1, ..., Pn-1 and I be a valid index, 
    the instantiation of the expansion P...[I] yields the pack element PI of P.

    Indexing a pack with non-constant expression index I is not allowed.

**********/

#include <iostream>

template<typename T, typename ... Args>
constexpr bool are_same_v = (std::is_same_v<T, Args> && ...);

template<typename T, typename ... Args>
struct first_arg {
    using type = T;
};


#ifdef __cpp_pack_indexing
    template<typename ... Args>
    using first_arg_t = Args...[0];
#else
    template<typename ... Args>
    using first_arg_t = typename first_arg<Args...>::type;
#endif

template<typename ... Args>
requires are_same_v<Args...>
first_arg_t<Args...> xadd(Args ... args) {
    return (... + args);
}

int main() {
    
    { std::cout << xadd(1) << '\n'; }
    { std::cout << xadd(1, 2, 3, 4) << '\n'; }
    //{ std::cout << xadd(1, "error", 3, 4) << '\n'; }

    return 0;
}

/*****
    END OF FILE
**********/


