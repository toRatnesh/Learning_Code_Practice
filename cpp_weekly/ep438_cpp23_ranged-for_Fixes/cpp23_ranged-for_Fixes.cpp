
/*****

References
    episode https://www.youtube.com/watch?v=G6FTtZCtFXU
    https://en.cppreference.com/w/cpp/language/range-for

This example demonstratea about C++23 fix for 
range-for loop in case of temporary values

pre C++23 it is UB to use range-for loop over a temporary

**********/

#include <iostream>
#include <string>
#include <vector>

class Thing {
    std::vector<int>     data{11, 12, 13, 14, 15, 16, 17, 18, 19};

    public:
    ~Thing()    { std::cout << "Destructor\n"; }
    Thing() { std::cout << "Constructor\n"; }

    Thing(const Thing &) { std::cout << "Copy Constructor\n"; }
    Thing(Thing &&) { std::cout << "Move Constructor\n"; }

    Thing & operator=(const Thing &) { std::cout << "Copy =\n";  return *this; }
    Thing & operator=(Thing &&) { std::cout << "Move =\n";  return *this; }

    const auto & getData() {
        return data;
    }
};

Thing make_thing() {
    return Thing{};
}

int main() {

    for(auto & elem : make_thing().getData()) // cpp20 GCC CW : warning: possibly dangling reference to a temporary
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    // pre C++23 fix
    for(auto thing = make_thing(); auto & elem : thing.getData()) // cpp20 GCC CW : warning: possibly dangling reference to a temporary
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


