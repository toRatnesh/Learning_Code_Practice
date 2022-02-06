/***********
  This example demonstartes the use of goto statement in CPP.
  For more info visit:
https://en.cppreference.com/w/cpp/language/goto

 **************/

#include <iostream>

int fun() {
a_label:
    std::clog << "a label\n";
    return 0;
}

int main() {

    // error in case goto skip initialization
    // error: jump to label 'b_label' from here crosses initialization of 'int i'
    goto b_label;

    int i = 0;

b_label:
    std::clog << i << ' ';
    ++i;if(i < 10) {
        goto b_label;
    }
    std::clog << '\n';

    for(size_t i = 0; i < 10; ++i) {
        if(i == 5)
            goto c_label;
        if(i == 7) {;
            // label can't be used out of scope
            //  error: label 'a_label' used but not defined
            goto a_label;
        }           

    }

    {
        // a label should follow by a statement
        // error: expected primary-expression before '}' token
c_label:
        //std::clog << "c label\n";
    }

    return 0;
}

/***********
  END OF FILE
 ************/
