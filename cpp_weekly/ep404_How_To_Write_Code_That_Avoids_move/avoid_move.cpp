/*****

    This examples demonstrates about how to write code that uses copy elision instead of move

    NOTE:
    Writing code that relies on simple composable function instead of relying on std::move is always better

    For more info visit:
    episode https://www.youtube.com/watch?v=6SaUwqw4ueE

**********/

#include <iostream>
#include <string>
#include <array>

class S {
    int     data;
    public:
    ~S() { std::puts("~S()"); }

    S() { std::puts("S()"); }
    S(int val)  : data(val) { std::puts("S(int)"); }

    S(const S & other) : data(other.data) { std::puts("S(const S &)"); }
    S(S && other) : data(std::move(other.data)) { std::puts("S(S &&)"); }

    S& operator=(const S & other) { 
        if(&other != this) {
            data = other.data;
        }
        return *this; 
    }
    S& operator=(S && other) { 
        if(&other != this) {
            data = std::move(other.data);
        }
        return *this; 
    }
};

S makeS(int val) {
    S s{val};
    return s;
}

int main() {

    {
        std::puts("=== Using copy ===");
        S s1{5};
        S s2{6};
        std::array<S, 2> as{s1, s2};
    }

    {
        std::puts("=== Using move ===");
        S s1{5};
        S s2{6};
        std::array<S, 2> as{std::move(s1), std::move(s2)};
        // Using move still uses 4 objects
    }

    {
        std::puts("=== Using composable function ===");
        std::array<S, 2> as{makeS(5), makeS(6)};
        // using composable function uses only 2 objects
    }

    return 0;
}

/*****
    END OF FILE
**********/


