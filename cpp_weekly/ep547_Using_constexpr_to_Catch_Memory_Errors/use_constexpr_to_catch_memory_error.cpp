/*****

References:
    episode     https://www.youtube.com/watch?v=-LAXqqqX274

    code        https://godbolt.org/z/ETeEfoj84

    This example demonstrates about how we could use 
    constexpr evaluation to catch memory error

    try to introduce memory error in this example while it being 
    evaluated as constexpr and see the reuslt

**********/

#include <iostream>
#include <utility>
#include <cassert>


template<typename T>
class nonstd_unique_ptr {
    //T   * mptr;
    T   * mptr{nullptr};


    constexpr void swap(nonstd_unique_ptr & other) {
        std::swap(mptr, other.mptr);
    }

    public:

    constexpr ~nonstd_unique_ptr() {
        delete mptr;
    }

    nonstd_unique_ptr() = default;
    constexpr nonstd_unique_ptr(T * ptr) : mptr{ptr} { }

    constexpr nonstd_unique_ptr(const nonstd_unique_ptr& ) = delete;
    constexpr nonstd_unique_ptr & operator=(const nonstd_unique_ptr& ) = delete;

    constexpr nonstd_unique_ptr(nonstd_unique_ptr&& other)
        : mptr{std::exchange(other.mptr, nullptr)} {

    }

    constexpr nonstd_unique_ptr & operator=(nonstd_unique_ptr&& other)
    {
        nonstd_unique_ptr{std::move(other)}.swap(*this);
        return *this;
    }

    constexpr T & operator*() const {
        return *mptr;
    }

};


int main() {

    consteval {
        [[maybe_unused]] nonstd_unique_ptr<int>   ptr1;
        [[maybe_unused]] nonstd_unique_ptr<int>   ptr2{};
        [[maybe_unused]] nonstd_unique_ptr<int>   ptr3{nullptr};

        [[maybe_unused]] nonstd_unique_ptr<int>   ptr4{new int{14}};
        //[[maybe_unused]] nonstd_unique_ptr<int>   ptr5{ptr4};
        //ptr1 = ptr4;

        [[maybe_unused]] nonstd_unique_ptr<int>   ptr6{new int{16}};
        [[maybe_unused]] nonstd_unique_ptr<int>   ptr7{std::move(ptr6)};
        ptr1 = std::move(ptr7);

        assert(*ptr1 == 16);
    }

    return 0;
}

/*****
    END OF FILE
**********/

