/***********
    This example demonstrates the use of c++17 std::as_const.
    as_const:
        Forms lvalue reference to const type of t

    For more info visit:
    https://en.cppreference.com/w/cpp/utility/as_const
    Tutorial video: https://www.youtube.com/watch?v=w996YXhkpkE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=292
 
 ************/

#include <iostream>
#include <string>
#include <utility> // for std::as_const

struct S {

    bool display() {
        std::puts("non-const version");
        return true;
    }

    bool display() const {
        std::puts("const version");
        return true;
    }

};

const S & as_const(const S & fp_s) {
    return fp_s;
}

template<typename T> 
const T & as_const_ver2(const T & fp_t) {
    return fp_t;
}

int main() {
    S s;
    s.display();
    const_cast<const S &>(s).display();
    as_const(s).display();
    as_const_ver2(s).display();
    std::as_const(s).display();
    return 0;
}

/*********
    END OF FILE
 ********/
