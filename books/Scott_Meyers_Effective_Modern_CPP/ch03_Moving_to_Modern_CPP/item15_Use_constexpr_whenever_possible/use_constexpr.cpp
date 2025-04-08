/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/constexpr

Item 15: Use constexpr whenever possible

	When applied to objects, it’s essentially a beefed-up form of const, 
		but when applied to functions, it has a quite different meaning

	Conceptually, constexpr indicates a value that’s not only constant, it’s known during compilation.
	Practically, you can’t assume that the results of constexpr functions are const, 
		nor can you take for granted that their values are known during compilation.

	constexpr objects
		Such objects are, in fact, const, and they do, in fact, have values that are known at compile time.
		
	Values known during compilation may be placed in read-only memory, 
		and can be used in contexts where C++ requires an integral constant expression.
		Example, array sizes
		
	const doesn’t offer the same guarantee as constexpr, 
		because const objects need not be initialized with values known during compilation
	Simply put, all constexpr objects are const, but not all const objects are constexpr.	
	constexpr 	->	const			✓
	const		->	constexpr		✗


	constexpr functions produce compile-time constants when they are called with compile-time constants.
	If they’re called with runtime values, they produce runtime values.

C++11 restrictions
	constexpr functions may contain no more than a single executable statement: a return
	Trick: "? :" and recursion can be used

	all built-in types except void qualify, but user-defined types may be literal, too, 
	because constructors and other member functions may be constexpr
	
	constexpr member functions are implicitly const

C++14 restrictions
	the restrictions on constexpr functions are substantially looser
	constexpr member functions are not implicitly const
	void type qualify

Summary:

• constexpr objects are const and are initialized with values known during compilation.
• constexpr functions can produce compile-time results when called with arguments whose values are known during compilation.
• constexpr objects and functions may be used in a wider range of contexts than non-constexpr objects and functions.
• constexpr is part of an object’s or function’s interface.

**********/

#include <iostream>
#include <array>

constexpr auto get_square(size_t val) {
    return (val * val);
}

class Point {
    double x, y;

    public:
    constexpr Point()   : x{0}, y{0} { }
    constexpr Point(double x, double y) : x{x}, y{y} { }

    constexpr double getX() const { return x; }
    constexpr double getY() const { return y; }

    constexpr void setX(const double ax) { x = ax; }
    constexpr void setY(const double ay) { y = ay; }

    constexpr bool operator==(const Point & p) const { 
        return ((x == p.x) && (y == p.y));
    }
};

constexpr Point midPoint(const Point & p1, const Point & p2) {
    return Point{ (p1.getX() + p2.getX())/2, (p1.getY() + p2.getY())/2 };
}

int main(const int argc, char *argv[]) {

    constexpr auto sval = get_square(5);
    static_assert(25 == sval, "Value is not 25");

    std::array<int, sval>   larr{};


    constexpr Point p1{5, 6};
    constexpr Point p2{3, 2};

    constexpr Point mp = midPoint(p1, p2);
    constexpr Point p3{4, 4};

    static_assert((mp == p3), "Point are not equal");


    //constexpr auto sqval = get_square(argc); // CE error: 'argc' is not a constant expression
    const auto sqval = get_square(argc);

    return 0;
}

/*****
    END OF FILE
**********/


