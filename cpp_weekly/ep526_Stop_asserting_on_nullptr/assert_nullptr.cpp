/*****

References:
    episode     https://www.youtube.com/watch?v=vivaDVFNj4U
    https://en.cppreference.com/w/cpp/error/assert.html

    Do not use std::assert as it might be removed in release build
    Better use reference or value

**********/

#include <iostream>
#include <cassert>

void poorCode(int * pdata) {
    assert(nullptr != pdata);
    std::cout << pdata << '\n';
}

void betterCodeByValue(int pdata) {
    std::cout << pdata << '\n';
}

void betterCodeByRef(int & pdata) {
    std::cout << pdata << '\n';
}

void betterCodeUseIfElse(int * pdata) {
    if(nullptr == pdata) {
        std::cout << "nullptr received\n";
    } else {
        std::cout << *pdata << '\n';
    }
}

int main()
{

    int *ptr = nullptr;
    int value{5};

    poorCode(ptr);
    betterCodeUseIfElse(ptr);

    betterCodeByValue(value);
    betterCodeByRef(value);

    return 0;
}

/*****
    END OF FILE
**********/

