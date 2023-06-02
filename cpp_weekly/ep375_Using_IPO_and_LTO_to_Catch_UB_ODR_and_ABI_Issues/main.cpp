/**********
    This example demonstrates about using IPO and LTO to catch UB and ODR issue in our code
*****************/


#include "get.h"
#include "use.h"

int main() {
    use_data(get_data());
    return 0;
}

/**********
    END OF FILE
*****************/