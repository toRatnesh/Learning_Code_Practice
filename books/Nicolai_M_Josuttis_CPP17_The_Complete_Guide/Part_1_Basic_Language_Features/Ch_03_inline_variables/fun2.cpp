
#include "fun2.hpp"
#include "common.hpp"

int fun2() {
    commonobj.display();
    return fun2_gval + common_gval + SomeType::someval.mval + Data::data;
}
