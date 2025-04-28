/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/lambda

Chapter 6 Lambda Expressions

Lambda expression
	A lambda expression is just that: an expression
	std::find_if(container.begin(), container.end(), [](int val) { return 0 < val && val < 10; });

Closure
	A closure is the runtime object created by a lambda. Depending on the capture mode, 
	closures hold copies of or references to the captured data.
	
	In the call to std::find_if above, the closure is the object 
	that’s passed at runtime as the third argument to std::find_if.
	
	closures may generally be copied

Closure class
	A closure class is a class from which a closure is instantiated.
	Each lambda causes compilers to generate a unique closure class.
	The statements inside a lambda become executable instructions in the member functions of its closure class.

Informally, it’s perfectly acceptable to blur the lines between lambdas, closures, and closure classes.


Item 31: Avoid default capture modes

Two default capture modes in C++11:
	1.	by-reference
	2.	by-value

	Default by-reference capture can lead to dangling references
	Default by-value capture lures you into thinking you’re immune to that problem (you’re not)


By-reference capture
	A by-reference capture causes a closure to contain a reference 
	to a local variable or to a parameter that’s available in the scope where the lambda is defined

	If the lifetime of a closure created from that lambda exceeds the lifetime 
	of the local variable or parameter, the reference in the closure will dangle.
	
	See example below
	

	the same problem would exist if by-reference capture were explicit
	
	but with an explicit capture, it’s easier to see that 
	the viability of the lambda is dependent on local varible lifetime

	
By-value capture
	A by-value capture causes a closure to contain a copy of the value
	
	but default by-value capture isn’t the antidangling solution always
	
	problem is that if you capture a pointer by value, 
	you copy the pointer into the closures arising from the lambda, 
	but you don’t prevent code outside the lambda from deleteing the pointer and causing your copies to dangle
	
	one example of this is use of default by-value capture inside a class member functions 
	will not copy data members of the class but instead it will copy this pointer
	
	if we want to capture the data member one solution is to make a local copy of the data member and copy it
	
	
	Lambda may be dependent also on variables like global variable, static storage duration variable
	These objects can be used inside lambdas, but they can’t be captured. 
	Yet specification of a default by-value capture mode can lend the impression that they are.
	
	{
		...
		static auto divisor = computeDivisor(calc1, calc2);						// now static
		filters.emplace_back([=](int value) { return value % divisor == 0;});	// captures nothing! refers to above static
		...
	}
	Practically speaking, this lambda captures divisor by reference, 
	a direct contradiction to what the default by-value capture clause seems to imply.
	
	Even in C++14, the advice of this Item to avoid default capture modes stands.

	
C++14 generalized lambda capture (Item 32)
	it is used to capture a member and make a copy of it explicit inside capture list

Summary
	•	Default by-reference capture can lead to dangling references.
	•	Default by-value capture is susceptible to dangling pointers (especially this), 
		and it misleadingly suggests that lambdas are self-contained.

**********/

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::function<double(double)>> geometry_area;

void add_square_area() {
    auto sqaure_area = [](const double parm) {
        std::clog << "Square area is ";
        return parm * parm;
    };
    geometry_area.push_back(sqaure_area);
}

// danger of capture by ref
void add_circle_area() {
    auto pi = 3.14;
    auto circle_area = [&](const double parm) {
        std::clog << "Circle area with unsafe value ref is ";
        return pi * parm * parm;  // ref to pi will dangle
    };
    geometry_area.push_back(circle_area);
}

// safe version - capture explicitly by value
void add_circle_area_safe() {
    auto pi = 3.14;
    auto circle_area = [pi](const double parm) {
        std::clog << "Circle area with safe explicit copy is ";
        return pi * parm * parm;
    };
    geometry_area.push_back(circle_area);
}

// danger of capture by value (pointer may be captured instead of value)
void add_circle_area_2() {
    double* pi = new double(3.14);
    auto circle_area = [=](const double parm) {
        std::clog << "Circle area with unsafe pointer copy is ";
        return (*pi) * parm * parm;  // pointer is copied instead of value
    };
    geometry_area.push_back(circle_area);
    delete pi;
    pi = nullptr;
}

// safe version - capture explicitly by value (do not copy pointer)
void add_circle_area_2_safe() {
    double* pi = new double(3.14);
    auto circle_area = [pi = *pi]( const double parm) {  // pi = *pi C++14 generic lambda capture
        std::clog << "Circle area with safe explicit copy of value from pointer is ";
        return pi *parm * parm;
    };
    geometry_area.push_back(circle_area);
    delete pi;
    pi = nullptr;
}

class Circle {
    double pi = 3.14;

   public:
    // error while capturing member varible
    void add_area() {
        auto area = [=](const double parm) {
            std::clog << "Circle area with unsafe copy of member varible is ";
            return pi * parm * parm;
        };  // this->pi is captured instead of pi
        geometry_area.push_back(area);
    }

    // error while capturing member varible
    void add_area_2() {
        static double pi = 4;
        
        auto area = [=](const double parm) {
            std::clog << "Circle area with unsafe copy of member varible is ";
            return pi * parm * parm;    // local static pi is captured instead of member variable pi, IT'S CAPTURED BY REFERENCE
            //return this->pi * parm * parm;
        };
        geometry_area.push_back(area);

        pi += 6;
    }

    // safe version
    void add_area_safe() {
        /* C++11
        double pi_copy = pi;
        auto area = [pi_copy](const double parm){ retunr pi_copy * parm * parm;};
        */
        auto area = [pi_copy = pi](const double parm) {
            std::clog << "Circle area with safe copy of member varible is ";
            return pi_copy * parm * parm;
        };  // C++14 generalized lambda capture
        geometry_area.push_back(area);
    }
};

void add_area_calculators() {
    add_square_area();
    // add_circle_area();
    add_circle_area_safe();
    // add_circle_area_2();
    add_circle_area_2_safe();

    Circle c;
    // c.add_area();
    c.add_area_2();
    c.add_area_safe();
}

int main() {
    add_area_calculators();

    const double parm = 5;
    for (auto area : geometry_area) {
        std::clog << std::fixed << area(parm) << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

