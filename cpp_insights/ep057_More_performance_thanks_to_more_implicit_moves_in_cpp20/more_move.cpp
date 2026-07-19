/*****

References
    episode https://www.youtube.com/watch?v=3CR1ow5BfJM
    
    DR11: Implicit move for more local objects and rvalue references 
    https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1825r0.html

    code https://godbolt.org/z/GWx3razn4

    since c++20 rvalue reference and more local objects can be moved

**********/

#include <iostream>


struct MoveOnly {
    MoveOnly() = default;
    MoveOnly(MoveOnly &&)   = default;
};


MoveOnly fun1(MoveOnly val) {
    return val;
}

MoveOnly fun2(MoveOnly && rval) {
    return rval;    // C++17 error: use of deleted function 'constexpr MoveOnly::MoveOnly(const MoveOnly&)'
}

int main() {

    return 0;
}

/*****
    END OF FILE
**********/

