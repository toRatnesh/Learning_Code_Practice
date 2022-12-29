
#include "common.h"
#include <iostream>

void printArray() {
    
    for(const auto & elem: garr<int, 5>) {
        std::clog << elem << ' ';
    }
    std::clog << '\n';

    for(const auto & elem: garr<int, 5u>) {
        std::clog << elem << '-';
    }
    
    std::clog << '\n';

}

