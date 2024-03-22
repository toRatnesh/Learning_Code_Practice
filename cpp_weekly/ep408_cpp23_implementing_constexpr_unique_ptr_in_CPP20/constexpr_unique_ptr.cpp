/*****

    std::unique_ptr has constexpr feature available since C++23
    This example deomstrates how such feature could be written in C++20


    For more info visit
    episode https://www.youtube.com/watch?v=E0QhZ6tNoRg
    https://en.cppreference.com/w/cpp/memory/unique_ptr

**********/

#include <iostream>
#include <memory>


// this is a rough implementation for representation purpose only
namespace nonstd {
    template<typename T>
    class unique_ptr {
        T   * data = nullptr;
        
        public:
        unique_ptr(const unique_ptr &)              = delete;
        unique_ptr& operator=(const unique_ptr &)   = delete;

        constexpr unique_ptr(unique_ptr &&) = default;
        constexpr unique_ptr& operator=(unique_ptr &&) = default;

        constexpr unique_ptr() = default;
        constexpr unique_ptr(T * data) : data(data) { }

        constexpr void reset() {
            delete data;
            data = nullptr;
        }

        constexpr ~unique_ptr() { reset(); }

        constexpr T operator*() {
            return *data;
        }
    };
}

constexpr int constexpr_nonstd_unique_ptr() {
    nonstd::unique_ptr<int>    data(new int(5));
    int val = *data;
    return val;
}

/*
constexpr int constexpr_unique_ptr() {
    std::unique_ptr<int>    data(new int(15));
    int val = *data;
    return val;
}

constexpr int constexpr_unique_ptr_02() {
    auto data = std::make_unique<int>(25);
    int val = *data;
    return val;
}
*/

int main() {
    //static_assert(15 == constexpr_unique_ptr());
    //static_assert(25 == constexpr_unique_ptr_02());

    static_assert(5 == constexpr_nonstd_unique_ptr());

    return 0;
}

/*****
    END OF FILE
**********/


