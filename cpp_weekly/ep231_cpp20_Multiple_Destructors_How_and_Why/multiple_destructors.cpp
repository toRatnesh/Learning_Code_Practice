/*******************
    This example demonstrates use of c++20 multiple destructors.
	
	For more info visit:
Episode video:	https://www.youtube.com/watch?v=A3_xrqr5Kdw&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=233
https://www.sandordargo.com/blog/2021/06/16/multiple-destructors-with-cpp-concepts
 
 ******************/

#include <utility>
#include <type_traits>
#include <string>

template<typename T>
struct myOptional {

    union {T t;};
    bool m_initialized = false;

    constexpr myOptional& operator=(T && other) {
        t = std::move(other);
        m_initialized = true;
        return *this;
    }

    constexpr ~myOptional() 
    requires(!std::is_trivially_destructible_v<T>)
    {
        if(m_initialized) {
            t.~T();
        }
    }

    constexpr ~myOptional() = default;
};

int main() {
    myOptional<int> obj;
    obj = 5;

    static_assert(std::is_trivially_destructible_v<myOptional<int>>);
    static_assert(!std::is_trivially_destructible_v<myOptional<std::string>>);

    return 0;
}

/********
    END OF FILE
 *******/
