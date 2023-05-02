#include "common.hpp"

int common() {
    commonobj.display();
    return common_gval + SomeType::someval.mval + Data::data;
}

