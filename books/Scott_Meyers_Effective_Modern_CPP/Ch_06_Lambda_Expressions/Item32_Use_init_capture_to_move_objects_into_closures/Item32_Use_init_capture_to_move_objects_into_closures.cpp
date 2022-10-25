/***********

References
    Effective Modern C++ | Scott Meyers

Item 32: Use C++14 init capture to move objects into closures
    Drawbacks of C++11 capture
        There is no way to capture move only objects
        It is not possible to capture the result of an expression
        Workaround: 
        In C++11, emulate C++14 init capture via hand-written classes or std::bind

    C++14 introduced C++14 init capture, that enables to specify
    i. the name of a data member in the closure class generated from the lambda and
    ii. an expression initializing that data member
    This is why C++14 init capture is also called generalized lambda capture.

    Drawbacks of C++14 init capture
        You can not express a default capture mode with an C++14 init capture

    auto lambda = [data_member=expression](){};
    The scope on the left is that of the closure class
    The scope on the right is the same as where the lambda is being defined

*************/

#include <iostream>
#include <vector>
#include <functional>
#include <memory>

std::vector<std::function<double(double param)>> geometry_area;

void add_square_area() {
    auto sqaure_area = [](double parm) { 
        std::clog << "Square area is ";
        return parm * parm; 
        };
    geometry_area.push_back(sqaure_area);
}

// danger of capture by ref
void add_circle_area() {
    auto pi = 3.14;
    auto circle_area = [&](double parm) {
        std::clog << "Circle area with unsafe value ref is "; 
        return pi * parm * parm; // ref to pi will dangle
        };
    geometry_area.push_back(circle_area);
}

// safe version - use C++14 init capture
void add_circle_area_safe() {
    auto pi = 3.14;
    auto circle_area = [pi = pi](double parm) {
        std::clog << "Circle area with safe explicit copy is ";
        return pi * parm * parm;
        };
    geometry_area.push_back(circle_area);
}

// danger of capture by value (pointer may be captured instead of value)
void add_circle_area_2() {
    double * pi = new double(3.14);
    auto circle_area = [=](double parm) {
        std::clog << "Circle area with unsafe pointer copy is ";
        return (*pi) * parm * parm; // pointer is copied instead of value
        };
    geometry_area.push_back(circle_area);
    delete pi; pi = nullptr;
}

// safe version - C++14 init capture to move unique pointer into closure
void add_circle_area_2_safe() {
    double * pi = new double(3.14);
    auto circle_area = [pi = *pi](double parm) {
        std::clog << "Circle area with safe explicit copy of value from pointer is ";
        return (pi) * parm * parm;
        };
    geometry_area.push_back(circle_area);
    delete pi; pi = nullptr;
}

class Circle {
    double pi = 3.14;
    public:
        // error while capturing member varible
        void add_area() {
            auto area = [=](int parm){ 
                std::clog << "Circle area with unsafe copy of member varible is ";
                return pi * parm * parm;}; // this->pi is captured instead of pi
            geometry_area.push_back(area);
        }

        // error while capturing member varible
        void add_area_2() {
            static double pi = 4;
            // local static pi is captured instead of member variable pi
            auto area = [=](int parm){ 
                std::clog << "Circle area with unsafe copy of member varible is ";
                return pi * parm * parm;}; // local pi is not captured because it's static, instead this->pi is captured
            geometry_area.push_back(area);
        }

        // safe version - C++14 init capture
        void add_area_safe() {
            /* C++11
            double pi_copy = pi;
            auto area = [pi_copy](int parm){ retunr pi_copy * parm * parm;};
            */
            auto area = [pi_copy = pi](int parm){ 
                std::clog << "Circle area with safe copy of member varible is ";
                return pi_copy * parm * parm;}; 
            geometry_area.push_back(area);
        }
};

void add_area_calculators() {
    add_square_area();
    add_circle_area();
    add_circle_area_safe();
    add_circle_area_2();
    add_circle_area_2_safe();

    Circle c;
    c.add_area();
    c.add_area_2();
    c.add_area_safe();
}

void capture_moveable_object() {
    auto up = std::make_unique<Circle>();
    auto lambda = [cr_up = std::move(up)]() { // capturing moved unique pointer
        cr_up->add_area();
        cr_up->add_area_2();
        cr_up->add_area_safe();
    };

    lambda();
}

int main() {
    add_area_calculators();

    capture_moveable_object();

    double parm = 5;
    for(auto area : geometry_area) {
        std::clog << std::fixed << area(parm) << '\n';
    }

    

    return 0;
}

/********
    END OF FILE
********/



