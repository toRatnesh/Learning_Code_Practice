/************
  This example demonstrates about lambda init capture.

  For more info visit:
https://en.cppreference.com/w/cpp/language/lambda


 ***********/


#include <iostream>

class S {
    int m;
    public:
 
    S(int v) : m(v) { }
 
    int get() {
        auto lbd = [=](){ return m+2; };

        std::clog << "lbd(): " << lbd() << '\n';
        ++m;
        std::clog << "lbd(): " << lbd() << '\n';

        return m;
    }
};

double gdv = 3.5;

int main() {

    S s{5};
    std::clog << s.get() << '\n';
    std::clog << '\n';

    static int st_i     = 5;
    const int ci        = 10;
    constexpr int cxp   = 15;
    const int & rci     = ci;

    auto lbd = [](){ 
        std::clog << "Using varibles without capture\n";
        std::clog << "global variable:          " << gdv << '\n';
        std::clog << "static local variable:    " << st_i << '\n';
        std::clog << "const local varible:      " << ci << '\n';
        std::clog << "constexpr local varible:  " << cxp << '\n';
        //std::clog << "const reference local variable: " << rci << '\n'
    };

    lbd();

    return 0;
}

/********
  END OF FILE
 ******/
