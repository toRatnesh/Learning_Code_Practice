/**************
    This example demonstrates about use of link time optimization 
    or inter procedural optimization

    For more info visit:
    https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
	Code edit: https://gcc.godbolt.org/z/E599E5scT
    
*****************/

#include "addition.hpp"

int getValue(int p, int q, int r) {
    return myadd(p, myadd(q,r));
}

int main() {
    return getValue(6, 7, 8);
}

/******************
    END OF FILE
*****************/