/*****

References

    episode https://www.youtube.com/watch?v=jf_OxE3j4AQ
    https://en.cppreference.com/w/cpp/utility/functional/function
    https://en.cppreference.com/w/cpp/utility/functional

    This episode demonstrates about functional programming present in C++

**********/

#include <iostream>
#include <string>
#include <functional>

template<typename Callable, typename T, typename U> 
auto call(Callable callable, T t, U u) {
    T res = callable(t, u);
    std::cout << res << '\n';
}

int afun(int a, int b) {
    return a+b;
}

template<typename T, typename U>
T atemp_fun(T a, U b) {
    return a+b;
}

struct S {
    template<typename T, typename U>
    T operator()(T a, U b) {
        return a+b;
    }
};

int main() {

    struct X {
        /* error: templates cannot be declared inside of a local class
        template<typename T, typename U>
        T operator()(T a, U b) {
            return a+b;
        }
        */

        int operator()(int a, int b) {
            return a+b;
        }

    };

    call(afun, 4, 5);
    //call(atemp_fun, 4, 5);
    call(S(), 4, 5);
    //call(X(), 4, 5);
    call([](int a, int b) { return a+b; }, 4, 5);
    call(std::plus<>(), 4, 5);

    return 0;
}

/*****
    END OF FILE
**********/

