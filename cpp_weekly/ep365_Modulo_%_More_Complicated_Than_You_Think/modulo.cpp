/***********

    This example demonstrates about various kind of modulo operations

    For more info visit
    episode https://www.youtube.com/watch?v=xVNYurap-lk
    https://en.wikipedia.org/wiki/Modulo
    https://stackoverflow.com/questions/1907565/c-and-python-different-behaviour-of-the-modulo-operation
    
*****************/

#include <iostream>
#include <cmath>
#include <iomanip>

int truncated(int dividend, int divisor) {
    return dividend - divisor * int(float(dividend) / float(divisor));
}

int floored(int dividend, int divisor) {
    return dividend -
           divisor * int(std::floor(float(dividend) / float(divisor)));
}

int floored_alt(int dividend, int divisor) {
    return ((dividend % divisor) + divisor) % divisor;
}

int euclidean(int dividend, int divisor) {
    return dividend -
           std::abs(divisor) *
               int(std::floor(float(dividend) / float(std::abs(divisor))));
}

int builtin(int dividend, int divisor) { return dividend % divisor; }

void run(int (*func)(int, int)) {
    for (int i = -4; i <= 4; ++i) {
        std::cout << i << " % 2: " << std::setw(2) <<  func(i, 2) << "   " << i << " % -2: " << std::setw(2) << func(i, -2) << '\n';
    }
}

int main() {

    std::cout << "=== builtin ===\n";
    run(builtin);
    std::cout << "=== euclidean ===\n";
    run(euclidean);
    std::cout << "=== floored_alt ===\n";
    run(floored_alt);
    std::cout << "=== floored ===\n";
    run(floored);
    std::cout << "=== truncated ===\n";
    run(truncated);

    std::cout << "=== std::remainder ===\n";
    std::cout << "std::remainder(7.2f, 5.1f) " << std::remainder(7.2f, 5.1f) << '\n';
    std::cout << "std::remainder(7.2, 5.1) " << std::remainder(7.2, 5.1) << '\n';
    
    return 0;
}

/*****
    END OF FILE
*********/



