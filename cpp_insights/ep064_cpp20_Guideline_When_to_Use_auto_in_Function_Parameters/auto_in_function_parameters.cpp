/*****

References

	episode https://www.youtube.com/watch?v=lJjrIfV3N_c
    code https://godbolt.org/z/8zK9PKz3P

    Guidelines:
    . Use auto only in case you do not need type 
    . Its better to use explicit template type instaed of auto for template functions

**********/

#include <iostream>
#include <string>

template<typename T>
T funAG(const T & val) {
    if constexpr(std::is_integral_v<T>) {
        std::cout << "integral vlaue: " << val << '\n';
    } else {
        std::cout << "vlaue: " << val << '\n';
    }

    return val;
}

auto funOG(const auto & val) {
    
    //if constexpr(std::is_integral_v<std::remove_reference_t<decltype(val)>>)      // THIS WILL WORK FINE
    if constexpr(std::is_integral_v<decltype(val)>) // std::is_integral_v<const int &> FAILS
    {
        std::cout << "integral vlaue: " << val << '\n';
    } else {
        std::cout << "vlaue: " << val << '\n';
    }

    return val;
}

int main() {

    funAG(std::string("behave as expected"));
    funOG(std::string("behave unusual"));

    funAG(3);
    funOG(3);

    return 0;
}

/*****
    END OF FILE
**********/

