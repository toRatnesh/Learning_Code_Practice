/********************

References:
        C++17 - The Complete Guide | Nicolai M. Josuttis

13. Placeholder Types like auto as Template Parameters

13.1 Using auto as Template Parameter

    Since C++17, you can use auto to declare a non-type template parameter
    NOTE: You can’t use this feature to get instantiations for types that in general are not allowed as template parameters
    We can even have a specific type as partial specialization
    Even class template argument deduction (CTAD) is supported
    You can also qualify auto, for example, to require the type of the template parameter to be a pointer
    By using variadic templates, you can parameterize templates to use a list of heterogeneous constant template arguments or a list of homogeneous constant template arguments

13.1.1 Parameterizing Templates for Characters and Strings
    allow passing both a character or a string as template parameter

13.1.2 Defining Metaprogramming Constants
    define compile-time constants more easily

*********************/

#include <iostream>
#include <string>
#include <array>

template<auto val>
auto display() { std::clog << val << '\n'; }

template<auto val> 
class S {
    public:
    void display() { std::clog << val << '\n'; }
};

// partial specialization
template<const char * val> 
class S<val> {
    public:
    void display() { std::clog << "Specialized for const char * : " << val << '\n'; }
};

// class template argument deduction (CTAD)
template<typename T, auto N>
class nonstdArray {
    std::array<T, N> m_arr{};
    public:
    nonstdArray(const std::array<T, N> & arr) : m_arr(arr) { 
        std::clog << "const std::array<T, N> & arr \n"; 
    }
    nonstdArray(T(&)[N] )  { 
        std::clog << "T(&)[N] \n";
    }
    void display() { for(const auto elem : m_arr) { std::clog << elem << ' '; } std::clog << '\n'; }
};

// qualify auto as pointer
template<const auto * ptr>
void display_ptr() {
    std::clog << *ptr << '\n';
}

// variadic templates
template<auto ... hetro_vals>
class HetroVal {
    public:
    void display() {
        auto printElem = [](const auto & elem) { std::clog << elem << ", "; };
        (..., printElem(hetro_vals));
        //(printElem(hetro_vals) ...);
        std::clog << '\n';
    }
};

template<auto val, decltype(val) ... homo_vals>
class HomoVal {
    public:
    void display() {
        auto printElem = [](const auto & elem) { std::clog << elem << ", "; };
        std::clog << val << ", ";
        (..., printElem(homo_vals));
        std::clog << '\n';
    }
};

// Parameterizing Templates for Characters and Strings
template <auto Sep = ' ', typename ... Args>
void print(const Args& ... args) {
    auto outWithSep = [](const auto& arg) { std::clog << arg << Sep; };
    (..., outWithSep(args));
    std::clog << '\n';
}

// Defining Metaprogramming Constants
template<auto v1, auto v2>
struct MyConstant {
    static constexpr auto min = v1;
    static constexpr auto max = v2;
};

char gmsg[] = "global const char aaray";
constexpr char gcmsg[] = "global constexpr char array";

int main() {

    {
        std::clog << "=== auto as Template Parameter\n";

        display<7>();
        display<'D'>();
        display<gmsg>();
        static char lsmsg[] = "static local const char array";
        display<lsmsg>();       
        static constexpr char lcmsg[] = "local constexpr char array";
        display<gcmsg>();
        display<lcmsg>();

        //display<7.5>(); // error: no matching function for call to 'display<7.5e+0>()'
        //display<"this results in compilation error">(); // error: no matching function for call to 'display<"this results in compilation error">()'
        [[maybe_unused]] char lmsg[] = "local const char array";
        //display<lmsg>(); // error: no matching function for call to 'display<lmsg>()'
        const std::string smsg = "sample string";
        //display<smsg>();    // error: no matching function for call to 'display<smsg>()'
    }
    
    {
        S<7>        s1;     s1.display();
        S<'D'>      s4;     s4.display();
        S<gmsg>     s2;     s2.display();
        static char lsmsg[] = "static local const char array";
        S<lsmsg>    s3;     s3.display();
        static constexpr char lcmsg[] = "local constexpr char array";
        S<gcmsg>    s5;     s5.display();
        S<lcmsg>    s6;     s6.display();
    }

    {
        std:: clog << "=== class template argument deduction (CTAD) \n";

        nonstdArray a1("hello");
        a1.display();

        std::array<double, 5> darr{1.1, 2.2, 3.3, 4.4, 5.5};
        nonstdArray a2{darr};
        a2.display();
    }

    {
        std:: clog << "=== qualify auto as pointer\n";

        static int val = 7;
        display_ptr<&val>();
        static char ch = 'D';
        display_ptr<&ch>();
        display_ptr<&gmsg>();
        static char lsmsg[] = "static local const char array";
        display_ptr<&lsmsg>();
        static constexpr char lcmsg[] = "local constexpr char array";
        display_ptr<&gcmsg>();
        display_ptr<&lcmsg>();
    }

    {
        std::clog << "=== variadic template\n";
        static char lmsg[] = "local static char array";
        HetroVal<1,lmsg,'A'> ht_val;    ht_val.display();

        HomoVal<1,2,3,'A'> hm_val;      hm_val.display();
        //HomoVal<1,2.2,3> hm_val;      hm_val.display(); // error: conversion from 'double' to 'int' in a converted constant expression
    }

    {
        std::clog << "=== Parameterizing Templates for Characters and Strings\n";
        std::string str{"world"};
        print(7.5, "hello", str);
    }

    {
        std::clog << "=== Defining Metaprogramming Constants\n";
        MyConstant<1, 100> mc;
        std::clog << "min value is " << mc.min << '\n';
        std::clog << "max value is " << mc.max << '\n';
    }

    return 0;
}

/*******
    END OF FILE
*********/
