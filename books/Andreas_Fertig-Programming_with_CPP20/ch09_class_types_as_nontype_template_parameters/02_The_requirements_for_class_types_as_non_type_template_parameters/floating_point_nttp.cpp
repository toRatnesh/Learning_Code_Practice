/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/template_parameters.html

Chapter 9 | Class-types as nontype template parameters

9.2 The requirements for class types as non-type template parameters

    Before C++20 we could use
    .   integral or enumeration types
    .   Pointers to object or function
    .   Reference to object or function
    .   std::nullptr_t

    NOTE:   the object must have static storage duration

    Since C++20 floating-point number is also allowed

    The definition for floating-point template arguments in C++ is now that
    two template arguments are considered equivalent if their values are
identical.

    In this case, value means bit pattern

**********/

#include <iostream>

template <double val>
struct UseDouble {
    static constexpr double value{val};
};

int main() {
    {
        // different bit pattern
        static_assert(not std::is_same_v<UseDouble<+0.0>, UseDouble<-0.0>>);
        static_assert(not std::is_same_v<UseDouble<1.2>, UseDouble<0.8 + 0.4>>);

        // according to IEEE -0.0 and +0.0 is same
        static_assert(-0.0 == +0.0);

        // same bit pattern
        static_assert(std::is_same_v<UseDouble<0.2>, UseDouble<0.1 + 0.1>>);
        static_assert(std::is_same_v<UseDouble<-0.6>, UseDouble<-0.3 - 0.3>>);
    }

    return 0;
}

/*****
    END OF FILE
**********/
