/*****

This example demonstrates about implementation of type_traits

References
    https://www.youtube.com/watch?v=g7D0F0qrs3I
    https://en.cppreference.com/w/cpp/header/type_traits

**********/

template<typename T, T v>
struct integral_const {
    static constexpr T value = v;
};


using true_type     = integral_const<bool, true>;
using false_type    = integral_const<bool, false>;

template<typename T>
struct is_pointer : false_type { };

template<typename T>
struct is_pointer<T*> : true_type { };

int main() {
    static_assert(not is_pointer<int>::value);
    static_assert(is_pointer<int *>::value);

    static_assert(not is_pointer<char>::value);
    static_assert(is_pointer<char *>::value);    
}

/*****
    END OF FILE
**********/


