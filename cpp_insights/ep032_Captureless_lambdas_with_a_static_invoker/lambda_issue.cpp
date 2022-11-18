/**********
    This example demonstrates about this bug fix in https://cppinsights.io/
    https://github.com/andreasfertig/cppinsights/issues/467

    For lambda without capture having static variable inside lambda body
    it suplicates code inside operator() function and equivalent funciton pointer version
    this bug has been fixed now

    For more info visit:
    https://github.com/andreasfertig/cppinsights/issues/467
    episode: https://www.youtube.com/watch?v=ubRdI4azR_Q

    Ouput with bug:
    1
    1

    Output after fix:
    1
    2

*********/

#include <iostream>

int main() {
    auto lambda = [](){
        static int val{0};
        std::clog << ++val << '\n';
    };

    lambda();
    (+lambda)();
    return 0;
}

/********
    END OF FILE
********/
