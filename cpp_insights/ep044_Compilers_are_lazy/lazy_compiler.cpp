/*****

Reference
    episode https://www.youtube.com/watch?v=IO5bhCHzQvA

    This example demonstrates about compiler lazy behavior
    For example for a class
        A constructor is generated when an object of that class is created
        A copy constructor is generated when an object is created using another
        A copy assignment operator is generated when an object is assigned to another

**********/

#include <utility>

class S {
    int m;
};

int main() {
    S s1;

    S s2(s1);
    S s3;
    s3 = s1;

    S s4 = std::move(s2);
    S s5;
    s5 = std::move(s3);
    return 0;
}

/*****
    END OF FILE
**********/


