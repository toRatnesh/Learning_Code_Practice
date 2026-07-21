/*****

References:
    episode     https://www.youtube.com/watch?v=dD6PhTJLz08
    https://cppreference.com/cpp/container/inplace_vector

    code https://godbolt.org/z/xccs6YW8s

    std::inplace_vector is a dynamically-resizable array with contiguous inplace storage. 
    The elements of type T are stored and properly aligned within the object itself. 
    The capacity of the internal storage is fixed at compile-time and is equal to N.

**********/

#include <print>
#include <inplace_vector>

int main()
{


    {
        constexpr std::inplace_vector<int, 5> vec{};
        static_assert(vec.capacity() == 5);
        static_assert(vec.size() == 0);

        std::println("Inplace vector capacity: {} size: {} elements: {}", 
            vec.capacity(), vec.size(), vec);
    }

    {   
        constexpr std::inplace_vector<int, 4> vec{1, 2, 3};
        static_assert(vec.capacity() == 4);
        static_assert(vec.size() == 3);

        std::println("Inplace vector capacity: {} size: {} elements: {}", 
            vec.capacity(), vec.size(), vec);
    }

    {
        // error: uncaught exception of type 'std::bad_alloc'; 'what()': 'std::bad_alloc'
        // constexpr std::inplace_vector<int, 4> vec{1, 2, 3, 4, 5};

        constexpr std::inplace_vector<int, 4> vec{1, 2, 3, 4};
        static_assert(vec.capacity() == 4);
        static_assert(vec.size() == 4);

        std::println("Inplace vector capacity: {} size: {} elements: {}", 
            vec.capacity(), vec.size(), vec);
    }
    

    {
        std::inplace_vector<int, 4> vec{1, 2, 3, 4};
        static_assert(vec.capacity() == 4);
        //static_assert(vec.size() == 4);

        std::println("Inplace vector capacity: {} size: {} elements: {}", 
            vec.capacity(), vec.size(), vec);

        try {
            vec.emplace_back(5);

            std::println("Inplace vector capacity: {} size: {} elements: {}", 
                vec.capacity(), vec.size(), vec);

        } catch (const std::exception & exp) {
            std::println("Exception: {}", exp.what());
        }

    }    

    return 0;
}

/*****
    END OF FILE
**********/

