/*****

References:
    episode     https://www.youtube.com/watch?v=gwwxD_l9T28
    https://en.cppreference.com/w/cpp/language/function.html#Deleted_functions

    Its better to mark a function as deleted than removing it from codebase

**********/

#include <iostream>

void fun(const double ) {
    std::puts("processing double");
}

void fun(const int ) = delete;

/*
void fun(const int ) {
    std::puts("processing integer");
}
*/

int main()
{
    fun(5.89);
    fun(34);
    fun(34.0f);

    return 0;
}

/*****
    END OF FILE
**********/
