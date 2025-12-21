/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/template_parameters.html

Chapter 9 | Class-types as nontype template parameters

9.1 What are non-type template parameters again

    C++ has three different kinds of templates parameters:
    1.  type template parameters            : we provide the type or compiler deduces the type
    2.  non-type template parameters NTTP   : we provide values
    3.  template template parameters

    As templates are instantiated during compile-time, 
    all the parameters we pass to them must be known at compile-time.

**********/

#include <iostream>

template<typename T, std::size_t N>
struct MyArr {
    T data[N];

    public:
    T & operator[](const std::size_t index) {
        return data[index];
    }

    const T & operator[](const std::size_t index) const {
        return data[index];
    }

};

int main() {

    {
        MyArr<int, 5> larr{1, 2, 3, 4, 5};
        std::cout << larr[3] << '\n'; 

        larr[3] = 6;       
        std::cout << larr[3] << '\n'; 
    }

    {
        const MyArr<int, 5> larr{1, 2, 3, 4, 5};
        std::cout << larr[3] << '\n'; 

        // CE error: assignment of read-only location 'larr.MyArr<int, 5>::operator[](3)'
        //larr[3] = 6;
        std::cout << larr[3] << '\n'; 
    }

    return 0;
}

/*****
    END OF FILE
**********/
