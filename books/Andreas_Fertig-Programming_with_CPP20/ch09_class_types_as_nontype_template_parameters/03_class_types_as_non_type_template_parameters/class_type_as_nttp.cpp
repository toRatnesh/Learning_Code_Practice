/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/template_parameters.html

Chapter 9 | Class-types as nontype template parameters

9.3 Class types as non-type template parameters

    for non-type template parameters we can use a literal type or, a literal class

    class is a literal class if it has
    .   a constexpr destructor. Since C++20, the implicit destructor is constexpr
    .   at least one constexpr constructor that is not a copy or move constructor
        A closure type or an aggregate, which don’t have a constructor, is also possible
    .   only non-volatile non-static data members and 
        base classes, which are literal types

9.3.1 A first contact with class types as NTTP
    in following example class StringView is as NTTP, sv is like a varible inside Data

9.3.2 What compile-time data do we have

    By using constexpr, we can create type safe replacements for macro

**********/

#include <iostream>
#include <algorithm>

template<typename C, std::size_t N>
struct StringView {
    char            data[N];
    std::size_t     size;

    constexpr StringView(const C (&str)[N]) : size{N} {
        std::copy_n(str, N, data);
    }
};


template<StringView sv> // class StringView as NTTP sv is like a varible inside Data
struct Data {

    void log() {
        std::cout << "Data size: " << sv.size << ", data: " << sv.data << '\n';
    }

};

int main() {

    Data<"C++ 20"> data{};
    data.log();

    return 0;
}

/*****
    END OF FILE
**********/
