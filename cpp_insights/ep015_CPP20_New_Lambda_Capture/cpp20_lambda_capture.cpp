/*****************
  This example demonstrates about the C++20 lambda capture.

  For more info visit:
  C++ Insights - Episode 15: C++20 New Lambda Capture | https://www.youtube.com/watch?v=UBe40ta9-Hg
  Lambda expressions | https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture

 *****************/

#include <iostream>

class S {
    int m;
    public:

    S(int a) : m(a) { }

    int get() { 
        auto lbd = 
            //[=, n = m]          // correct before C++20, since C++20 | warning: implicit capture of 'this' via '[=]' is deprecated in C++20 [-Wdeprecated]
            [=, this, n = m]  // correct since C++20, pre c++20 | warning: explicit by-copy capture of 'this' redundant with by-copy capture default
            (){
                std::clog << "Object capture by reference   | ";
                std::clog << "m: " << m << " n: " << n << '\n'; 
            };

        auto lbd2 = 
            [=, *this, n = m]  // since C++17
            (){ 
                std::clog << "Object capture by copy        | ";
                std::clog << "m: " << m << " n: " << n << '\n'; 
            };

        lbd();
        lbd2();

        ++m;

        lbd();
        lbd2();

        return m;
    }
};

int main() {
    S s(3);
    std::clog << s.get() << '\n';

    return 0;
}

/*******
  END OF FILE
 ********/
