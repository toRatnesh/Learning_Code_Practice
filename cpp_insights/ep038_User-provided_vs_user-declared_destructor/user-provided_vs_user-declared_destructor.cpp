/********
    
    This example demonstrates about difference bwtween 
    user provided vs user declared destructor

    user provided destrucot stops move opration 
    so when you do not have to do anything inside destructor do not write your own destructor

    For more info visit
    episode https://www.youtube.com/watch?v=fvFaXC8aip0

************/

#include <iostream>
#include <optional>

class Test {
    public:
    //~test() = default;    // compiler provided destructor
    // ~test() {}           // user provided destructor
    // ~test();
};

//test::~test() {}          // user provided destructor
//test::~test() = default;  // user provided destructor

int main() {
    std::optional<Test> tobj{};

    return 0;
}

/********
    END OF FILE
************/



