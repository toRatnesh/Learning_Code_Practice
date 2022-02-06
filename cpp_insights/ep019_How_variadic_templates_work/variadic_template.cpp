/**********
  This example demonstrates about variadic template parameter expansion

  For more info visit:
https://en.cppreference.com/w/cpp/language/parameter_pack
C++ Insights - Episode 19: How variadic templates work | https://www.youtube.com/watch?v=j1qpRgUhXtk
C++ Weekly | episode 6, 10, 48, 64, 65, 66
 ********/

#include <iostream>
#include <cmath>

template<typename T, typename ... Tv> 
auto cpp11_variadic_min(const T & first, const Tv& ...others) -> decltype(first) {

    auto lf_min = [](const T & v1, const T & v2){ return (v1 < v2) ? v1 : v2; }; // local lambda function for comparison of two elements

    T l_min = first;
    std::initializer_list<T> l_list{(l_min = lf_min(l_min, others))...};
    return *(std::next(l_list.begin(), l_list.size()-1));
    //return *(std::rbegin(l_list));  // C++14
}


// NOTE: this is not a vary good way because will generate multiple instantiation of this template function
template<typename T, typename ... Tv> 
auto cpp17_variadic_min(const T & first, const T & second, const Tv& ...others) {

    const auto res = (first < second) ? first : second;
    if constexpr(sizeof...(others) > 0) {       // constexpr is necessary
        return cpp17_variadic_min(res, others...);
    }

    return res;
}

// improved c++17 version from C++ weekly episode 64, 65
template<typename First, typename ... T>
decltype(auto) cpp17_variadic_min_improved(const First & f, const T & ... t) {
    First retval = f;
    ((retval = std::min(retval, t)), ...);
    return retval;
}


int main() {

    std::clog << cpp17_variadic_min(6, 5, 4, 3, 2) << '\n';
    std::clog << cpp11_variadic_min(6, 5, 4, 3, 2) << '\n';
    std::clog << cpp17_variadic_min_improved(6, 5, 4, 3, 2) << '\n';

    return 0;

}

/*****
  END OF FILE
 ****/

