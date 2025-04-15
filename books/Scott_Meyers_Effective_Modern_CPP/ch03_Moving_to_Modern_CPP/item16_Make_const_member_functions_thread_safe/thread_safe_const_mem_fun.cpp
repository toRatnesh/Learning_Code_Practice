/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/member_functions#Member_functions_with_cv-qualifiers

Item 16: Make const member functions thread safe

const member function
	const member function, represents a read operation
	Having multiple threads perform a read operation without synchronization is safe
	
const member function with mutable member
	if a mutable member is modified inside a const member function
	calling that const member function from multiple thread is undefined behavior
	because multiple threads are reading and writing to mutable member without synchronization
	
	The easiest way to address the issue is the usual one: employ a mutex
	
const member function and atomic
	
	For a single variable or memory location requiring synchronization, use of a std::atomic is adequate, 
	but once you get to two or more variables or memory locations that require manipulation as a unit, you should reach for a mutex.
	
	
Summary
• Make const member functions thread safe unless you’re certain they’ll never be used in a concurrent context.
• Use of std::atomic variables may offer better performance than a mutex, 
	but they’re suited for manipulation of only a single variable or memory location.

**********/

#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <memory>
#include <chrono>

class Point {
    double  x;
    double  y;

    mutable uint32_t count = 0;
    mutable std::atomic<uint32_t> acount{0};
    
    public:

    Point(const double x, const double y) : x(x), y(y) { }

    double distaceFromPoint(const Point & p = {0, 0}) const  {
        ++count;
        ++acount;
        auto d = std::sqrt(((p.x - x) * (p.x - x)) + ((p.y - y) * (p.y - y)));
        return d;
    }

    void display() const { std::cout << "Point is {" << x << "," << y << "}\n"; }
    uint32_t getCount() const { return count; }
    uint32_t getAtomicCount() const { return acount; }
};

int expensiveComputation1() { return 1; }
int expensiveComputation2() { return 2; }

class Widget {

    // for thread safety
    mutable std::mutex m;
    mutable int cachedValue{0};                 // no longer atomic
    mutable bool cacheValid{ false };        // no longer atomic

    // multiple atomic are thread unsafe
    // mutable std::atomic<bool> cacheValid { false };
    // mutable std::atomic<int> cachedValue{0};    

public:

    int magicValue() const {

        std::lock_guard<std::mutex> guard(m);
        
        if (cacheValid) {
            std::cout << "Magic value-1: " << cachedValue << '\n';
            return cachedValue;
        }
        else {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            
            cachedValue = val1 + val2;
            cacheValid = true;
            std::cout << "Magic value-2: " << cachedValue << '\n';
            return cachedValue;
        }
    }
};

int main() {

    {
        Point p{3.0, 4.0};
        p.display();
        std::cout << p.distaceFromPoint() << '\n';
    }
    std::cout << '\n';

    {
        //const Point p{3.0, 4.0};
	auto p = std::make_shared<Point>(3.0, 4.0);
	//auto p2 = std::make_shared<Point>(3.0, 4.0);
        static Point p2{0.0, 0.0};

        { std::thread t(&Point::distaceFromPoint, p, std::cref(p2));     t.detach(); }
        { std::thread t(&Point::distaceFromPoint, p, std::cref(p2));     t.detach(); }
        { std::thread t(&Point::distaceFromPoint, p, std::cref(p2));     t.detach(); }
        { std::thread t(&Point::distaceFromPoint, p, std::cref(p2));     t.detach(); }
        { std::thread t(&Point::distaceFromPoint, p, std::cref(p2));     t.detach(); }

        std::cout << "Count " << p->getCount() << '\n';
        std::cout << "Atomic Count " << p->getAtomicCount() << '\n';
    }
    std::cout << '\n';

    {
        //Widget w;
	auto w = std::make_shared<Widget>();
        { std::thread t(&Widget::magicValue, w);     t.detach(); }
        { std::thread t(&Widget::magicValue, w);     t.detach(); }
        { std::thread t(&Widget::magicValue, w);     t.detach(); }
        { std::thread t(&Widget::magicValue, w);     t.detach(); }
        { std::thread t(&Widget::magicValue, w);     t.detach(); }
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}

/*****
    END OF FILE
**********/


