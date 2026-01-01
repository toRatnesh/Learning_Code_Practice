/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/explicit.html

Chapter 11 | Language Updates

11.4 conditional explicit

    explicit ( expression )

    Since C++20 The explicit specifier may be used with a constant expression. 
    The function is explicit if and only if that constant expression evaluates to true.

11.4.1 Writing a well behaved wrapper

11.4.2 Communicate your intention, explicitly

    absence of explicit() raises doubt whether it is intentionally or not 
    using explicit makes our intention clear

**********/

#include <format>
#include <iostream>

struct Point2D {
    double  x;
    double  y;

    Point2D() : x{0}, y{0} { }
    Point2D(const double x, const double y) : x{x}, y{y} { }

    // absence of explicit raises doubt whether it is intentionally or not
    //Point2D(const double x) : x{x}, y{0} { } 
    explicit(false) Point2D(const double x) : x{x}, y{0} { } 
};

struct Point3D {
    Point2D p;
    double  z;

    Point3D() : p{}, z{0} { }
    Point3D(const double x, const double y, const double z) : p{x, y}, z{z} { }

    explicit Point3D(const double x) : p{x}, z{0} { }
    explicit Point3D(const Point2D & p) : p{p}, z{0} { }
};

void displayPoint(const Point2D & p) {
    std::cout << std::format("{{{}, {}}}\n", p.x, p.y);
}

void displayPoint3d(const Point3D & p) {
    std::cout << std::format("{{{}, {}, {}}}\n", p.p.x, p.p.y, p.z);
}

int main() {

    {   const Point2D p;        displayPoint(p);    }
    {   const Point2D p{3, 4};  displayPoint(p);    }
    {   const Point2D p{3};     displayPoint(p);    }
    {   displayPoint(5);    } // double in convertible to Point2D


    {   
        const Point2D p{3};
        //displayPoint3d(p);      // error: no matching function for call to 'displayPoint3d'
    }

    {   
        const Point2D p2{3};
        const Point3D p3{p2};
        displayPoint3d(p3);
    }

    {
        //displayPoint3d(4);  // error: no matching function for call to 'displayPoint3d'
    }

    return 0; 
}

/*****
    END OF FILE
**********/


