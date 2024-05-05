
/*****
    ep382_Static_Initialization_Order_Fiasco_and_cpp20_constinit

    This example demonstrates about issue with static initialization
    in case of one static object is using another



    1. Strongly avoid global mutable objects
    2. global statics that rely on each other are bad, because we cannot guarantee initialization order (Static Initialization Order Fiasco)
    3. constexpr constructible statics are naturally "constant initialized"
    4. constinit does not change the meaning of our code, it validates our assumptions

**********/


#include "consumer.hpp"
#include "provider.hpp"

int main() {

    return 0;
}

/*****
    END OF FILE
**********/
