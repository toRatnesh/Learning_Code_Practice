/***********

References
    Effective Modern C++ | Scott Meyers

Item 31: Avoid default capture modes
    two default capture modes in C++11: 
        i.  by-reference 
        ii. by-value

Default by-reference capture
    Capture by-reference causes a closure to contain a reference to a local variable or to a parameter that's available in the scope where the lambda is defined.
    If the lifetime of a closure created from that lambda exceeds the lifetime of the local variable or parameter, the reference in the closure will dangle. Like if we pass the lambda to a thread which excutes beyond lifetime of the local variable;

Default by-value capture
    Problem is if you capture a pointer by value, you copy the pointer into the closures arising from the lambda, but you don.t prevent code outside the lambda from deleteing the pointer and causing your copies to dangle.
    It also misleads that lambda are self contained.

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

// safe version - capture explicitly by value
void add_circle_area_safe() {
    auto pi = 3.14;
    auto circle_area = [pi](double parm) {
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

// safe version - capture explicitly by value (do not copy pointer)
void add_circle_area_2_safe() {
    double * pi = new double(3.14);
    auto circle_area = [pi = *pi](double parm) { // pi = *pi C++14 generic lambda capture
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

        // safe version
        void add_area_safe() {
            /* C++11
            double pi_copy = pi;
            auto area = [pi_copy](int parm){ retunr pi_copy * parm * parm;};
            */
            auto area = [pi_copy = pi](int parm){ 
                std::clog << "Circle area with safe copy of member varible is ";
                return pi_copy * parm * parm;}; // C++14 generalized lambda capture
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

int main() {
    add_area_calculators();

    double parm = 5;
    for(auto area : geometry_area) {
        std::clog << std::fixed << area(parm) << '\n';
    }

    return 0;
}

/********
    END OF FILE
********/


