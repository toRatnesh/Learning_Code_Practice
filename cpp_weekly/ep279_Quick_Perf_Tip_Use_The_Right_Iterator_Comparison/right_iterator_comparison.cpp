/*************
    This exmaple demonstrtes about the use of right iterator comparison.
    This also demonstrates how using best practices of using range based for loop avoids this pitfall.

 *************/

#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec;
    vec.emplace_back(10, 'A');
    vec.emplace_back(10, 'B');
    vec.emplace_back(10, 'C');
    vec.emplace_back(10, 'D');
    vec.emplace_back(10, 'E');
    // wrong iterator comparison
    for(auto it = vec.begin(); it < vec.end(); ++it) {
        std::puts((*it).c_str());
    }

    // right iterator comparison
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::puts((*it).c_str());
    }

    // best practice : use range based for loop it's equivalent to right iterator comparison
    for(auto & elem : vec) {
        std::puts(elem.c_str());
    }

    return 0;
}


/******
  END OF FILE
 ******/

