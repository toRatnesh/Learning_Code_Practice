/*****

References
    Effective Modern C++ | Scott Meyers


Chapter 7: Templates and Generic Programming

    Generic programming — the ability to write code that is independent of the types of objects being manipulated

    It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
    that execute inside C++ compilers and that stop running when compilation is complete.

Item 46: Define non-member functions inside templates when type conversions are desired

    From Item 24: Declare non-member functions when type conversions should apply to all parameters
    If you need type conversions on all parameters to a function (including the one that would otherwise be pointed 
    to by the this pointer), the function must be a non-member.


	to support mixed-mode arithmetic, we want the code below to compile.
		New_Point2D<int> p = 6 + p2;

	CASE -1 | Writing operator+ as free template function for New_Point2D
		
		this fails to compile
		In non template version compilers know what function we’re trying to call (operator+ taking two Point2D)
		
		In template version compilers do not know which function we want to call. 
		Instead, they’re trying to figure out what function to instantiate
		
		operator+’s first parameter is declared to be of type New_Point2D<T>, but the first argument passed to operator+ (6) is of type int
		How are compilers to figure out what T is in this case? 
		You might expect them to use New_Point2D<int>’s non-explicit constructor to convert 6 into a New_Point2D<int>, 
		thus allowing them to deduce that T is int, but they don’t do that. 
		They don’t, because implicit type conversion functions are never considered during template argument deduction.
		Such conversions are used during function calls

	CASE -2 | declare operator+ for New_Point2D<T> as a member friend function

		class New_Point2D<T> can declare operator* for New_Point2D<T> as a friend function. 
		Class templates don’t depend on template argument deduction (that process applies only to function templates), 
		so T is always known at the time the class New_Point2D<T> is instantiated. 
		That makes it easy for the New_Point2D<T> class to declare the appropriate operator+ function as a friend
		
		As a declared function (not a function template), compilers can use implicit conversion functions 
		(such as New_Point2D’s non-explicit constructor) when calling it, and that’s how they make the mixed mode call succeed.
		
		although the code will compile, it won’t link

	CASE -3 | define operator+ for New_Point2D<T> as a member friend function
		
		merge the body of operator+ into its declaration
		mixed-mode calls to operator+ now compile, link, and run

	CASE -4 | Improvements
		functions defined inside a class are implicitly declared inline, and that includes friend functions like operator+
		
		You can minimize the impact of such inline declarations by having operator+ do 
		nothing but call a helper function defined outside of the class


	In order to make type conversions possible on all arguments, we need a non-member function (Item 24 still applies); 
	and in order to have the proper function automatically instantiated, we need to declare the function inside the class.	
		
	Summary:
		When writing a class template that offers functions related to the template that support implicit type conversions 
		on all parameters, define those functions as friends inside the class template.

**********/

#include <iostream>
#include <string>
#include <sstream>


class Point2D {
    int m_x;
    int m_y;

    public:

    Point2D(const int x = 0, const int y = 0) {
        m_x = x;
        m_y = y;
    }

    int x() const { return m_x; }
    int y() const { return m_y; }

    std::string str() {
        std::ostringstream l_oss;
        l_oss << "{" << m_x  << ',' << m_y << "}";
        return l_oss.str();
    }
};

Point2D operator+(const Point2D & point1, const Point2D & point2) {
    return Point2D(point1.x() + point2.x(), point1.y() + point2.y());
}


template<typename T>
class New_Point2D {
    T m_x;
    T m_y;

    public:

    New_Point2D(const T x = 0, const T y = 0) {
        m_x = x;
        m_y = y;
    }

    T x() const { return m_x; }
    T y() const { return m_y; }

    std::string str() {
        std::ostringstream l_oss;
        l_oss << "{" << m_x  << ',' << m_y << "}";
        return l_oss.str();
    }

    //  CASE -2
    //friend New_Point2D operator+(const New_Point2D & point1, const New_Point2D & point2); // CASE-1

    //  CASE -3
    //friend New_Point2D operator+(const New_Point2D & point1, const New_Point2D & point2) {
    //    return New_Point2D(point1.x() + point2.x(), point1.y() + point2.y());
    //}

    // CASE -4
    friend New_Point2D operator+(const New_Point2D & point1, const New_Point2D & point2) {
        return xadd(point1, point2);
    }
};


// CASE -1
//template<typename T>
//New_Point2D<T> operator+(const New_Point2D<T> & point1, const New_Point2D<T> & point2) {
//    return New_Point2D<T>(point1.x() + point2.x(), point1.y() + point2.y());
//}

// CASE -4
template<typename T>
New_Point2D<T> xadd(const New_Point2D<T> & point1, const New_Point2D<T> & point2) {
    return New_Point2D<T>(point1.x() + point2.x(), point1.y() + point2.y());
}

int main() {

    
    {
        Point2D p1(2, 5);
        Point2D p2(6, 9);

        std::cout << "Point-1 " << p1.str() << '\n';
        std::cout << "Point-2 " << p2.str() << '\n';

        {
            Point2D p = p1 + p2;
            std::cout << "Sum of Point-1 and Point-2 " << p.str() << '\n';            
        }
        {
            Point2D p = 6 + p2;
            std::cout << "Sum of 6 and Point-2 " << p.str() << '\n';            
        }        
    }
    std::cout << '\n';
    

    {
        New_Point2D<int> p1(2, 5);
        New_Point2D<int> p2(6, 9);

        std::cout << "Point-1 " << p1.str() << '\n';
        std::cout << "Point-2 " << p2.str() << '\n';

        {
            New_Point2D<int> p = p1 + p2;
            std::cout << "Sum of Point-1 and Point-2 " << p.str() << '\n';            
        }
        {
            New_Point2D<int> p = 6 + p2;
            std::cout << "Sum of 6 and Point-2 " << p.str() << '\n';            
        }        
    }


    return 0;
}

/*****
    END OF FILE
**********/
