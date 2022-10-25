
#include "fun1.hpp"
#include "common.hpp"

int fun1() {
    commonobj.display();
    return fun1_gval + common_gval + SomeType::someval.mval + Data::data;
}
