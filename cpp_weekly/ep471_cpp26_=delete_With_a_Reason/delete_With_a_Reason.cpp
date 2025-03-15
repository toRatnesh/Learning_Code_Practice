/*****

References

    episode https://www.youtube.com/watch?v=9iFJRCHwSok
    https://en.cppreference.com/w/cpp/language/function#Deleted_functions

= delete ;                      (since C++11)

= delete ( string-literal );    (since C++26)
    shows the rationale for deletion or to suggest an alternative

**********/

#include <print>

void fun(int val) { std::println("val is {}", val); }

void tun(int val) { std::println("val is {}", val); }
void tun(double val) = delete("To prevent implicit conversion");

int main() {
    fun(23);
    fun(23.67); // warning: implicit conversion from 'double' to 'int' changes value from 23.67 to 23

    tun(23);
    //tun(23.67); // CE error: call to deleted function 'tun': To prevent implicit conversion

    return 0;
}

/*****
    END OF FILE
**********/

