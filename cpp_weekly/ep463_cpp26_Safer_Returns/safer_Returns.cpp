/*****

References

    episode https://www.youtube.com/watch?v=T4g92jtGkXM

    Since C++26 returning a tempory is an error

**********/

#include <iostream>

int get_value() {
    int val = 5;
    return val;
}

const int & get_ref_val() {
    return get_value(); // CE error: returning reference to temporary
}

int main() {


    return 0;
}

/*****
    END OF FILE
**********/

