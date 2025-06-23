/*****

ep055_References_are_no_pointers

References

	episode https://www.youtube.com/watch?v=Oz0LzNpTk6c

    In C++ references are not pointers they are only alias to the variable

**********/

#include <iostream>
#include <string>

#define LOGEXP(x) std::cout << #x << ": " << x << '\n';

int main() {

    std::string sval{"sample string value"};
    LOGEXP(sval);
    LOGEXP(&sval);
    std::cout << '\n';

    std::string * sptr = &sval;
    LOGEXP(*sptr);
    LOGEXP(sptr);
    std::cout << '\n';

    std::string & sref = sval;
    LOGEXP(sref);
    LOGEXP(&sref);
    std::cout << '\n';

    std::string sval2{"updated string value"};
    LOGEXP(sval2);
    LOGEXP(&sval2);      


    sref = sval2;   // sref still refers to sval, this assignment changes the value of sval
    LOGEXP(sref);
    LOGEXP(&sref);

    LOGEXP(sval);
    LOGEXP(&sval);    

    return 0;
}

/*****
    END OF FILE
**********/
