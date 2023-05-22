/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.4 Polymorphism and Inhomogeneous Collections with std::variant
	std::variant enables a new form of polymorphism and dealing with inhomogeneous collections
	compile-time polymorphism with a close set of data types
	we can program that at runtime for different types different functions/methods are called (without any need for virtual functions, references, and pointers)

16.4.1 Geometric Objects with std::variant

	First, we define a common data type for all possible types
	using shape_variant_t = std::variant<Line, Circle, Rectangle>;
	
	This code would not be possible with runtime polymorphism, because then the types would have to have shape_variant_t as a common base class we would need a vector of pointers of shape_variant_t elements, and because of pointers we would have to create the objects with new so that we have to track when to call delete or use smart pointers
	
	called draw() functions don’t have to be virtual
	If the type interfaces differ, we can use compile-time if or visitor overloading to deal with this situation

************/

#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct Coordinate {
    int x;
    int y;
};

class Circle {
    Coordinate  center;
    unsigned    radius;
    public:
    Circle(Coordinate cord, unsigned rad) 
        : center{cord}, radius{rad} { }
    
    void draw() const {
        std::cout << "Circle center: {" << center.x << "," << center.y << "}    radius: " << radius << '\n'; 
    }

};

class Line {
    Coordinate  point1, point2;
    public:
    Line(Coordinate p1, Coordinate p2) 
        : point1{p1}, point2{p2} { }
    
    void draw() const {
        std::cout << "Line Point-1: {"  << point1.x << "," << point1.y << 
        "} Point-2: {" << point2.x << "," << point2.y << "}\n";
    }

};

class Rectangle {
    Coordinate  point1, point2;
    public:
    Rectangle(Coordinate p1, Coordinate p2) 
        : point1{p1}, point2{p2} { }
    
    void display() const {
        std::cout << "Rectangle Diagonal Point-1: {"  << point1.x << "," << point1.y << 
        "} Point-2: {" << point2.x << "," << point2.y << "}\n";
    }

};

using shape_variant_t = std::variant<Line, Circle, Rectangle>;

std::vector<shape_variant_t> getFigureCollection() {
    std::vector<shape_variant_t> shapes;
    shapes.push_back(Line{Coordinate{0,0}, Coordinate{5,5}});
    shapes.push_back(Circle{Coordinate{7,7}, 4});
    shapes.push_back(Rectangle{Coordinate{1,1}, Coordinate{8,8}});
    return shapes;
}


int main() {
    std::cout << "=== std::variant<> compile time polymorphism ===\n";
    std::vector<shape_variant_t> shape_coll = getFigureCollection();
    for(const auto & shape_varv : shape_coll) {
        std::visit(
            [](const auto & shape){ 
                if constexpr(std::is_same_v<const Rectangle &, decltype(shape)>) {
                    shape.display();  // handling different interface with if constexpr
                } else {
                    shape.draw(); 
                }
            
            },  shape_varv);
    }
    return 0;
}

/*********
    END OF FILE
************/


