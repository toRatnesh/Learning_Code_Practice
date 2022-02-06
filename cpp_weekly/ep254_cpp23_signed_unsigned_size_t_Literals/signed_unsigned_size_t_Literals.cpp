/************
  This example demonstrates about C++23 feature of literal suffix for size_t.

  For more info visit:
https://en.cppreference.com/w/cpp/language/integer_literal

 **********/

#include <vector>

int main() {
    std::vector lv = {1,2,3,4,5,6};
    for(auto i = 0; i < lv.size(); ++i) {

    }

    for(auto i = 0zu; i < lv.size(); ++i) {

    }

    return 0;
}

/********
  END OF FILE
 *******/
