/*****

References
    episode:    https://www.youtube.com/watch?v=pwf45vaXm3Q
    https://en.cppreference.com/w/cpp/language/static_assert.html

    C++23 change
    "allow static_assert of non-value-dependent expressions in a template context"
    but retroactive!
    not C++ version dependent, compiler dependent

**********/

#include <iostream>
#include <type_traits>

template<typename T>
T test(T val)
{
  if constexpr (std::is_same_v<T, int>) {
    static_assert(false);
  } else {
    return val;
  }
}

template<typename T>
T testImproved(T val)
{
    return val;
}

// delete is better option
template<>
int testImproved(int val) = delete;     // mark the function taking int as delete


int main()
{
    {

        {
            auto val = test<float>(2.35f);
            std::cout << val << '\n';
        }

        {
            auto val = test<bool>(true);
            std::cout << std::boolalpha << val << '\n';
        }

        {
            auto val = test<double>(12.35);
            std::cout << val << '\n';
        }

        {
            //auto val = test<int>(12);
            //std::cout << val << '\n';
        }

        }

    {
        {
            auto val = testImproved<float>(2.35f);
            std::cout << val << '\n';
        }

        {
            auto val = testImproved<bool>(true);
            std::cout << std::boolalpha << val << '\n';
        }

        {
            auto val = testImproved<double>(12.35);
            std::cout << val << '\n';
        }

        {
            //auto val = testImproved<int>(12);
            //std::cout << val << '\n';
        }    
    }

    return 0;
}

/*****
    END OF FILE
**********/

