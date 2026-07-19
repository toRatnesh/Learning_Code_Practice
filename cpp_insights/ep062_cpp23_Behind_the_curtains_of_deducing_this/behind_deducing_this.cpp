/*****

References

	episode https://www.youtube.com/watch?v=bo4VzJb61uI
    https://cppreference.com/cpp/language/function#Explicit_object_parameter
    https://cppreference.com/cpp/language/member_functions#Explicit_object_member_functions

    https://devblogs.microsoft.com/cppblog/cpp23-deducing-this/
    https://www.sandordargo.com/blog/2022/02/16/deducing-this-cpp23

    Code https://godbolt.org/z/757dcabhr
    
Deducing this
==============

Explicit object parameter:
---------------------------

    A parameter declaration with the specifier this declares an explicit object parameter.

    An explicit object parameter cannot be a function parameter pack, and it can only appear as the first parameter of the parameter list in the following declarations:

    a declaration of a member function or member function template
    an explicit instantiation or explicit specialization of a templated member function
    a lambda declaration
    A member function with an explicit object parameter has the following restrictions:

    The function is not static.
    The function is not virtual.
    The declarator of the function does not contain cv and ref.

Explicit object member functions:
----------------------------------

    For a non-static non-virtual member function not declared with cv-qualifier or ref-qualifier, 
    its first parameter, if not being a function parameter pack, 
    can be an explicit object parameter (denoted with the prefixed keyword this)

**********/

#include <iostream>

namespace nonstd {

    template<typename T, size_t SIZE>
    struct array {
        T       m_arr[SIZE];


        T & operator[](const int idx)   { return m_arr[idx]; }
        const T & operator[](const int idx) const   { return m_arr[idx]; } 

        constexpr size_t size() const { return SIZE; }

        T*  data() { return m_arr; }
        const T*  data() const { return m_arr; }

        T* begin() { return data(); }
        T* end() { return data() + size(); }

        const T* begin() const { return data(); }
        const T* end() const { return data() + size(); }
    };
}

namespace nonstd23 {

    template<typename T, size_t SIZE>
    struct array {
        T       m_arr[SIZE];

        auto & operator[](this auto & self, const int idx)   { return self.m_arr[idx]; }

        constexpr size_t size() const { return SIZE; }

        auto*  data(this auto & self) { return self.m_arr; }

        auto* begin(this auto & self) { return self.data(); }
        auto* end(this auto & self) { return self.data() + self.size(); }
    };
}

int main() {

    {
        nonstd::array<int, 10> larr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        for(const auto & elem : larr) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';    
    }

    {
        nonstd23::array<int, 10> larr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        for(const auto & elem : larr) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';    
    }

    {
        const nonstd23::array<int, 10> larr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        for(const auto & elem : larr) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';    
    }

    return 0;
}

/*****
    END OF FILE
**********/

