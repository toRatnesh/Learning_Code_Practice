/*****

Reference:
    C++ Insights - Episode 42: C++20: When is a struct an aggregate
    https://www.youtube.com/watch?v=VxRz5LC373w
    
    https://en.cppreference.com/w/cpp/language/aggregate_initialization

This example demonstrates about breaking changes in C++20 for aggregate initialization

	T object = { .des1 = arg1 , .des2 { arg2 } ... };	(3)	(since C++20)
	T object { .des1 = arg1 , .des2 { arg2 } ... };		(4)	(since C++20)

    ->    no user-provided, inherited, or explicit constructors   (since C++11) (until C++20)
    ->    no user-declared or inherited constructors              (since C++20)
    
Aggregate initialization
    Initializes an aggregate from an initializer list. It is a form of list-initialization. 


Definitions
    An aggregate is one of the following types:

    array type
    class type (typically, struct or union), that has
    ->    no user-declared constructors                           (until C++11)

    ->    no user-provided, inherited, or explicit constructors   (since C++11) (until C++20)
    ->    no user-declared or inherited constructors              (since C++20)
    
    ->    no private or protected direct (since C++17) non-static data members
    ->    no base classes                                         (until C++17)
    ->    no virtual base classes
          no private or protected direct base classes             (since C++17)
    
    ->    no virtual member functions
    ->    no default member initializers                          (since C++11) (until C++14)

    The elements of an aggregate are:
    ->    for an array, the array elements in increasing subscript order, or
    ->    for a class, the non-static data members that are not anonymous bit-fields, in declaration order.   (until C++17)
    ->    for a class, the direct base classes in declaration order,  followed by the direct non-static data members 
          that are neither anonymous bit-fields nor members of an anonymous union,  in declaration order.     (since C++17)

**********/

#include <string>

struct StAggregateCpp20 {
    int ival;
    double dval;
    bool bval;
    std::string sval;
};

struct StNoAggregateCpp20 {
    int ival;
    double dval;
    bool bval;
    std::string sval;

    StNoAggregateCpp20() = default;
};

class ClAggregateCpp20 {
   public:
    int ival;
    double dval;
    bool bval;
    std::string sval;
};

class ClNoAggregateCpp20 {
   public:
    int ival;
    double dval;
    bool bval;
    std::string sval;

    ClNoAggregateCpp20() = default;
};

int main() {
    StAggregateCpp20 ag20{1, 2.5, true, "sample string"};
    { StAggregateCpp20 ag20{.ival = 1, .dval = 2.5, .bval = true, .sval = "sample string"};  }  // valid C++20

    // CE error: no matching constructor for initialization of 'StNoAggregateCpp20' 
    // StNoAggregateCpp20   nag20{1, 2.5, true, "sample string"};                               // valid C++17

    ClAggregateCpp20 cag20{1, 2.5, true, "sample string"};
    { ClAggregateCpp20 cag20{.ival = 1, .dval = 2.5, .bval = true, .sval = "sample string"}; }  // valid C++20

    // CE error: no matching constructor for initialization of 'ClNoAggregateCpp20'
    // ClNoAggregateCpp20 cnag20{1, 2.5, true, "sample string"};                                // valid C++17

    return 0;
}

/*****
    END OF FILE
**********/


