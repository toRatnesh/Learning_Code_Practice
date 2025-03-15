/*****

References

    episode https://www.youtube.com/watch?v=ZuTJAP4oMwg
    https://en.cppreference.com/w/cpp/language/rule_of_three


    This example demonstrates about how move operation can be broken by defining destructor.
    To overcome this problem follow the rule of zero or rule of five.

**********/

#include <iostream>
#include <string>

struct Data {
    ~Data() { std::puts("~Data()"); }
    
    Data() { std::puts("Data()"); }
    
    Data(const Data &) { std::puts("Data(const Data &)"); }
    Data(Data &&) { std::puts("Data(Data &&)"); }

    Data& operator=(const Data &) { std::puts("Data& operator=(const Data &)"); return *this; }
    Data& operator=(Data &&) { std::puts("Data& operator=(Data &&)"); return *this; }
};

struct St {
    Data data;  
};

struct S {
    Data data;
    ~S(){}
};

int main() {
    {
        std::puts("Defining destructor only breaks move operation");
        static_assert(std::is_move_constructible_v<S>);
        static_assert(std::is_constructible_v<S, S&&>);

        S s1;
        S s2 = std::move(s1);
    }
    
    {
        std::puts("Unbroken move operation in absence of destructor");
        static_assert(std::is_move_constructible_v<St>);
        static_assert(std::is_constructible_v<St, St&&>);

        St st1;
        St st2 = std::move(st1);
    }

    return 0;
}

/*****
    END OF FILE
**********/

