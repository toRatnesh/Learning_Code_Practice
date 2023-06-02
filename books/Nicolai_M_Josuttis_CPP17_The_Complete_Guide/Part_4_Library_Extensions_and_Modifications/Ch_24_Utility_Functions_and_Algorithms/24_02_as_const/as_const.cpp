/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/as_const

Chapter 24 Other Utility Functions and Algorithms
	C++17 provides a couple of new utility functions and algorithms

24.2 as_const()
	converts values to the corresponding const values without using static_cast<> or the add_const_t<> type trait
	
24.2.1 Capturing by Const Reference
	Application:	ability to capture lambda parameters by const reference
	
*************/

#include <iostream>
#include <utility>
#include <vector>

class S {
    public:
    void display() { std::cout << "Inside a member function\n"; }
    void display() const { std::cout << "Inside a const member function\n"; }
};

int main() {
    std::cout << "=== as_const() ===\n";
    S s;
    s.display();                    // calls non-const version
    std::as_const(s).display();     // calls const version

    
    {
        std::vector lvec{3, 5, 1, 7, 3, 8, 3, 9};
        auto display_coll = [&coll = lvec](){
            std::cout <<  "Collection elements:\n";
            coll.push_back(13);
            for(const auto & elem : coll) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        };
        display_coll();
    }
    
    {
        std::cout << "=== Lambda Capturing by Const Reference ===\n";
        std::vector lvec{3, 5, 1, 7, 3, 8, 3, 9};
        auto display_coll = [&coll = std::as_const(lvec)](){
            std::cout <<  "Collection elements:\n";
            // CE error: passing 'const std::vector<int, std::allocator<int> >' as 'this' argument discards qualifiers
            //coll.push_back(13);
            for(const auto & elem : coll) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';
        };
        display_coll();
    }

    return 0;
}

/**********
    END OF FILE
*************/


