/*****

References:
    episode     https://www.youtube.com/watch?v=41YdzJ-Jx48
    https://cppreference.com/cpp/language/function#Function_declaration
    Code        https://godbolt.org/z/1WsG19r5f

    This example demonstrats about why we should still use trailing return types

    . they are consistent with lambda
    . they are consistent with deduction guide
    . consistent with almost always auto style
    . have cleaner syntax for auto deduction of reference return types

**********/

#include <iostream>
#include <array>

auto getValue() {
    return 35;
}

template<typename T1, typename T2>
auto xadd1(T1 v1, T2 v2) 
{
    return v1 + v2;
}

template<typename T1, typename T2>
auto xadd2(T1 v1, T2 v2) -> decltype(v1 + v2) 
{
    return v1 + v2;
}

template<typename T1, typename T2>
decltype(std::declval<T1>() + std::declval<T2>()) xadd3(T1 v1, T2 v2)
{
    return v1 + v2;
}

template<typename T1, typename T2>
auto xadd4(T1 v1, T2 v2) -> decltype(auto) 
{
    return v1 + v2;
}

template<typename T1, typename T2>
auto  xadd5(T1 && v1, T2 && v2) -> decltype(std::forward<T1>(v1) + std::forward<T2>(v2))
{
    return std::forward<T1>(v1) + std::forward<T2>(v2);
}

template<typename T1, typename T2>
auto  xadd6(T1 && v1, T2 && v2) -> decltype(auto)
{
    return std::forward<T1>(v1) + std::forward<T2>(v2);
}


void use_lambda() {
    // they are consistent with lambda
    auto l = []() -> float { return 7.5f; };
    auto val = l();
    std::cout << val << '\n';
}

// they are consistent with deduction guide

template<typename T>
struct Data { 
    T data;
};

template<typename T>
Data(const T & ) -> Data<T>;

auto getValue2() -> auto {
    // consistent with almost always auto style
    auto val = 9.5;
    return val;
}


void using_fun_pointer() 
{
    // trailing return type in function pointer

    using fptr = auto(*)(float) -> int;
    fptr p = [](float fval) -> int { return static_cast<int>(fval); };
    auto val = p(10.5f);
    std::cout << val << '\n';
}

auto getStaticData() -> const auto & 
{
    constexpr static std::array data{1, 2, 3, 4, 5};
    return data;

}

//int main() 
//auto main()
auto main() -> int  // main must return int
{
    { auto val = getValue(); std::cout << val << '\n'; }
    { auto val = xadd1(1, 0.5); std::cout << val << '\n';  }
    { auto val = xadd2(2, 0.5); std::cout << val << '\n';  }
    { auto val = xadd3(3, 0.5); std::cout << val << '\n';  }
    { auto val = xadd4(4, 0.5); std::cout << val << '\n';  }
    { auto val = xadd5(5, 0.5); std::cout << val << '\n';  }
    { auto val = xadd6(6, 0.5); std::cout << val << '\n';  }
    use_lambda();

    {
        Data d{8.5};
        auto val = d.data;
        std::cout << val << '\n';        
    }

    { auto val = getValue2(); std::cout << val << '\n'; }

    using_fun_pointer();

    {
        auto arr = getStaticData();
        for(const auto & val : arr) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }


    return 0;
}

/*****
    END OF FILE
**********/

