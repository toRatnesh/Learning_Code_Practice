/****************
  This example demonstrates about captureless lambda.
  Captureless lambda has no state and are compatible with function pointer.

  For more info visit:
  C++ Insights - Episode 17: The Internal of Captureless Lambdas | https://www.youtube.com/watch?v=KWZ7iKoWg7w

 *******************/

#include <iostream>

int main() {

    auto lbd = [](int m, double d){ return m*d;};
    std::clog << lbd(4,2.5) << '\n';

    double (*fun)(int, double) = lbd;
    std::clog << fun(8, 2.5) << '\n';

    using fp = double (*)(int, double);
    fp fp1 = lbd;
    std::clog << fp1(10, 2.5) << '\n';


    // lambda with capture
    auto lbd2 = [r=5](int m, double d){ return m*d*r;};
    std::clog << lbd2(4,2.5) << '\n';

    // lambda with captures are not compatible with function pointer
    //double (*fun2)(int, double) = lbd2; // error: cannot convert 'main()::<lambda(int, double)>' to 'double (*)(int, double)' in initialization
    //fp fp2 = lbd2;  // error: cannot convert 'main()::<lambda(int, double)>' to 'fp' {aka 'double (*)(int, double)'} in initialization

    return 0;
}

/********
  END OF FILE
 ********/
