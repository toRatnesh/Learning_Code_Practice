/********
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021

  This example demonstrates the concept demonstrated in the above cppcon conference video.
  For more info visit:
  Back to Basics: Lambdas - Nicolai Josuttis - CppCon 2021 | https://www.youtube.com/watch?v=IgNUBw3vcO4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=6
https://en.cppreference.com/w/cpp/language/lambda
https://www.fluentcpp.com/2021/12/13/the-evolutions-of-lambdas-in-c14-c17-and-c20/

 *******/

/********************
  This example demonstrates about diffrences of Generic Lambda and Generic Temaplate Function


  ->  Generic lambda and generic template function ae different
  ->  A lambda is not a function template
  ->  Generic function can not be passed as callable (we need to use decltype to pass type)
  ->  Generic function using auto since C++20 are still generic template function 
  ->  Prefer lambda over generic templte function

 ****************/

#include <iostream>
#include <vector>
#include <functional>

auto printColl = [](const auto & coll){
    for(const auto & elem: coll) {
        std::clog << elem << ' ';
    }
    std::clog << '\n';
};

template<typename T> 
void printColl2(const T & coll) {
    for(const auto & elem: coll) {
        std::clog << elem << ' ';
    }
    std::clog << '\n';  
}

int main() {

    std::vector coll = {1,2,3,4,5,6,7,8,9,10};

    printColl(coll);
    printColl2(coll);

    std::invoke(printColl, coll);
    //std::invoke(printColl2, coll);  // call fails with template function
    std::invoke(printColl2<decltype(coll)>, coll);  // need to use decltype to pass type

    return 0;
}

/******
  END OF FILE
 ********/
