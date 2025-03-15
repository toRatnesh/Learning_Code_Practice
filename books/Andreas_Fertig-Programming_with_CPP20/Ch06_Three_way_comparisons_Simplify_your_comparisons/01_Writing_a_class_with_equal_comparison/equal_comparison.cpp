/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

Chapter 6 | Threeway comparisons: Simplify your comparisons

    spaceship operator, helps us write less code when defining comparisons

    Consider a basic case where you needed to provide an operator== which did something special.
    For consistency reasons, you usually would have provided operator != as well.
    But what was its implementation?
    Well, in all cases I can remember, the implementation was this:

    bool operator!=(const T& t) { return !(*this == t); }

    That is not special code. It is absolutely trivial, but has to be written, reviewed and maintained. 
    Let’s see how C++20 tackles this corner.

6.1 Writing a class with equal comparison

    Let’s write a class with member function operator== inside the class
    But to make not equal (!=) work as well, we have to provide an operator for that too

6.1.1 Comparing different types

    Consider the scenario where comparison should also work in case where 
    a value is provided with plain internal data type of the member use for comparison inside class

    In addition to the two original methods, we needed two additional overloads, defined as friend-functions, 
    plus two more overloads for swapped arguments. 
    The boiler-plate code just increased by a lot.


6.1.2 Less handwritten code with operator reverse, rewrite and =default

    C++20 enables us to apply =default, which we gained with C++11, here as well, requesting the compiler to fill in the blanks.

    In C++20, we only need the two functions provided in following code.
    The reasons for it are two new abilities of the compiler operator reverse and rewrite, which are explained in detail in section 6.6.

**********/

#include <iostream>

class Point {
    int x, y;

    public:
    Point(const int x, const int y) : x(x), y(y) { }
    
    bool operator==(const Point & p) const {
        return ((x == p.x) && (y == p.y));
    }
    bool operator!=(const Point & p) const {
        return not((*this) == p);
    }

    friend bool operator==(const Point & p, const int val);
    friend bool operator!=(const Point & p, const int val);

    friend bool operator==(const int val, const Point & p);
    friend bool operator!=(const int val, const Point & p);
    
};

bool operator==(const int val, const Point & p) {
    return (val == p.x);
}
bool operator!=(const int val, const Point & p) {
    return not(val == p.x);
}

bool operator==(const Point & p, const int val) {
    return (val == p.x);
}
bool operator!=(const Point & p, const int val) {
    return not(val == p.x);
}


class Point_20 {
    int x, y;

    public:
    Point_20(const int x, const int y) : x(x), y(y) { }
    /*
    In C++20, we only need the two functions provided in following code.
    The reasons for it are two new abilities of the compiler operator reverse and rewrite, (section 6.6).
    */
    bool operator==(const Point_20 & p) const = default;
    bool operator==(const int val) const {
        return (val == x);
    }    
};

int main() {
    {
        std::cout << "=== 6.1.1 Comparing different types ===\n";
        Point p1{3, 4};
        Point p2{4, 5};

        [[maybe_unused]] const bool res11 = (p1 == p2);
        [[maybe_unused]] const bool res12 = (p1 == 3);
        [[maybe_unused]] const bool res13 = (5 == p1);

        [[maybe_unused]] const bool res21 = (p1 != p2);
        [[maybe_unused]] const bool res22 = (p1 != 3);
        [[maybe_unused]] const bool res23 = (5 != p1);

        std::cout << std::boolalpha << res11 << ' ' << res12 << ' ' << res13 << '\n' 
        << res21 << ' ' << res22 << ' ' << res23 << '\n';
    }

    {
        std::cout << "=== 6.1.2 operator reverse, rewrite and =default ===\n";
        Point_20 p1{3, 4};
        Point_20 p2{4, 5};

        [[maybe_unused]] const bool res11 = (p1 == p2);
        [[maybe_unused]] const bool res12 = (p1 == 3);
        [[maybe_unused]] const bool res13 = (5 == p1);

        [[maybe_unused]] const bool res21 = (p1 != p2);
        [[maybe_unused]] const bool res22 = (p1 != 3);
        [[maybe_unused]] const bool res23 = (5 != p1);

        std::cout << std::boolalpha << res11 << ' ' << res12 << ' ' << res13 << '\n' 
        << res21 << ' ' << res22 << ' ' << res23 << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

