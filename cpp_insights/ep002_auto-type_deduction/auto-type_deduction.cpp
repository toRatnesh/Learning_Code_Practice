/********
  This example demonstrates about auto type deduction
  For more info watch cpp weekly episode 287 and 296

  For detail of type deduction compile this code in https://cppinsights.io/
 *******/

#include <initializer_list>

int main() {

    auto x = 39;
    const auto cx = x;
    const auto& rx = x;

    auto && ref1 = x;
    auto && ref2 = cx;
    auto && ref3 = rx;
    auto && ref4 = 39;


    auto x1 = 39;
    auto x2(39);
    auto x3 = {39};
    auto x4{39};

    int * ip;
    const int * cip;
    const int* const cicp = ip;

    auto aip = ip;
    auto acip = cip;
    auto acicp = cicp;
    auto* const acicp2 = cicp;

    return 0;
}

/******
  END OF FILE
 ******/
