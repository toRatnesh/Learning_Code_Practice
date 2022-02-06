/***************
  This example demonstrates use of vector and string in constexpr context.
    NOTE:   vector or string are used in constexpr context they are not constexpr.

  In this example Jason present many different scenarios for detail must watch this episode. 

  For more info visit:
https://www.youtube.com/watch?v=cuFILbHp-RA&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=270

 **************/

#include <vector>
#include <numeric>

constexpr auto getVec() {
    std::vector<int> lv{1,2,3,4,5};
    return lv;
}

constexpr auto sum() {
    const auto lv = getVec();
    return std::accumulate(lv.begin(), lv.end(), 0);
}

int main() {
    constexpr auto res = sum();
    return 0;
}

/*********
  END OF FILE
 *********/

