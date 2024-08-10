/*****

References
    episode https://www.youtube.com/watch?v=PTCFddZfnXc
    https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wnrvo

    Warn if the compiler does not elide the copy from a local variable to 
    the return value of a function in a context where it is allowed by [class.copy.elision]. 
    This elision is commonly known as the Named Return Value Optimization (NRVO).
    
**********/

#include <iostream>
#include <string>

std::string fun_nrvo() {
    std::string val{"string NRVO"};
    return val;
}

std::string fun_rvo() {
    return "string RVO";
}

std::string get_string_01(const bool flag) {
    std::string val1{"string-1"};
    std::string val2{"string-2"};

    if(flag) {
        return val1;
    } else {
        return val2;
    }
}

std::string get_string_02(const bool flag) {
    if(flag) {
        std::string val1{"string-1"};
        return val1;
    } else {
        std::string val2{"string-2"};
        return val2;
    }
}

std::string get_string_03(const bool flag) {
    if(flag) {
        return "string-1";
    } else {
        return "string-2";
    }
}

std::string get_string_04() {
    std::string val = get_string_03(true);
    val += " modified";
    return val;
}

int main() {

    {std::string val = fun_nrvo(); }
    {std::string val = fun_rvo(); }

    {std::string val = get_string_01(true); }
    {std::string val = get_string_02(false); }
    {std::string val = get_string_03(true); }
    {std::string val = get_string_04(); }

    return 0;
}

/*****
    END OF FILE
**********/


