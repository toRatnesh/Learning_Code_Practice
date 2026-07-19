/*****

References

	episode https://www.youtube.com/watch?v=Ly9rD6D5iew
    https://cppreference.com/cpp/language/explicit

    code https://godbolt.org/z/4r5e33W9W
    

    explicit	            (1)	
    explicit ( expression )	(2)	(since C++20)

    1)  Specifies that a constructor or conversion function(since C++11) 
        or deduction guide(since C++17) is explicit, that is, 
        it cannot be used for implicit conversions and copy-initialization.
    
    2)  The explicit specifier may be used with a constant expression.
        The function is explicit if and only if that constant expression evaluates to true.

**********/

#include <iostream>

class Point2d {
    int m_x, m_y;

    public:
    explicit Point2d(const int x) : m_x{x}, m_y{0} { }
    Point2d(const int x, const int y) : m_x{x}, m_y{y} { }

    int x() { return m_x; }
    int y() { return m_y; }
};

void display(Point2d p) {
    std::cout << "x: " << p.x() << ", y: " << p.y() << '\n';
}

template<typename T>
struct Wrapper {

    T m_data;
    
    /*  VERSION-1   | WRONG, THIS ALLOWS IMPLICIT CONVERSION FROM U TO T
    template<typename U>
    Wrapper(const U & val) : m_data{val} { }
    */

    /*  VERSION-2   | CORRECT, USING SFINAE TO MARK EXPLICIT CONVERSION WHEN U IS NOT COVERTIBLE TO T
    template<typename U, std::enable_if_t<std::is_convertible_v<U, T>, bool> = true>
    Wrapper(const U & val) : m_data{val} { }

    template<typename U, std::enable_if_t<(not std::is_convertible_v<U, T>), bool> = true>
    explicit Wrapper(const U & val) : m_data{val} { }
    */

    // VERSION - 3 | C++20 conditional explciit
    template<typename U>
    explicit(not std::is_convertible_v<U, T>) Wrapper(const U & val) : m_data{val} { }

    T data() { return m_data; }

};

void viewIt(Wrapper<Point2d> p) {
    std::cout << "x: " << p.data().x() << ", y: " << p.data().y() << '\n';
}

int main() {

    {
        { display(Point2d{3}); }
        { display(Point2d{3, 4}); }
        //{ display(2); } // error: could not convert '2' from 'int' to 'Point2d'
    }
    std::cout << '\n';

    {
        { viewIt(Point2d{3}); }
        { viewIt(Point2d{3, 4}); }
        
        //{ viewIt(2); }         // WORKS IN VERSION-1 WHICH IS WRONG
        { viewIt(Point2d{2}); }
    }

    return 0;
}

/*****
    END OF FILE
**********/



