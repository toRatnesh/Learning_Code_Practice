/*****

References

	episode https://www.youtube.com/watch?v=qjWo62dw-4s

    code https://godbolt.org/z/Gns434x97

    This example demonstrates about use of C++20 concepts
    
    In this example c++20 concept is used to make a class conditional copybale

    Same class is made non-cpyable using inheritance from a class which is non-copyable

**********/

#include <iostream>
#include <string>

template<typename T, bool = std::is_trivially_copy_constructible_v<T>>
struct xoptional_copy_base{ };

template<typename T>
struct xoptional_copy_base<T, false>{ 
    xoptional_copy_base()   = default;
    xoptional_copy_base(xoptional_copy_base &&)    = default;
};

template<typename T>
class xoptional : private xoptional_copy_base<T>{

    public:
    xoptional(const T & ) { }

    // c++20  concepts
    //xoptional(const xoptional & ) requires(std::is_trivially_copy_constructible_v<T>) = default;
};

class NonCopyable {
    int value;

    public:
    NonCopyable(const int val) : value{val} {}
    NonCopyable(const NonCopyable &)    = delete;
};

int main() {

    {
        xoptional<int>  data1{5};
        xoptional<int>  data2{data1};
    }

    {
        xoptional<NonCopyable>  data1{NonCopyable{5}};
        xoptional<NonCopyable>  data2{data1};
    }

    return 0;
}

/*****
    END OF FILE
**********/

