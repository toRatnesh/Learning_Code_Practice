/**************
    This example demonstrates about use of link time optimization 
    or inter procedural optimization

    For more info visit:
    https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
    

*****************/
#include "static.hpp"
#include "dynamic.hpp"
#include "common.hpp"

int gval = 5;

int main() {
    int res1 = static_sum(6,7);
    int res2 = dynamic_sum(6,7);
    return static_sum(6,7);
}

/******************
    END OF FILE
*****************/