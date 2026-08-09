/*****

References:
    episode     https://www.youtube.com/watch?v=T-d8l3s4Nx8
    https://en.cppreference.com/cpp/container/array

    code https://godbolt.org/z/McdT7sYv5

    This example demonstrates about constexpr propety of std::array

**********/

#include <array>

int main()
{

    {
        constexpr std::array<int, 5> larr{1, 2, 3, 4, 5};
        
        static_assert(larr[2] == 3);
        static_assert(larr.at(2) == 3);
        
        static_assert(larr.front() == 1);
        static_assert(larr.back() == 5);

        static_assert(*larr.data() == 1);

        static_assert(larr.size() == 5);
        static_assert(not larr.empty());
        
        static_assert(*larr.begin() == 1);
        static_assert(*(larr.end() - 1) == 5);        

        static_assert(*(larr.rend() - 1) == 1);
        static_assert(*larr.rbegin() == 5); 

    }

    return 0;
}

/*****
    END OF FILE
**********/

