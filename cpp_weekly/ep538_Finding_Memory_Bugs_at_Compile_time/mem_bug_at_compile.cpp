/****

References

	episode https://www.youtube.com/watch?v=FZaoT7Kx_L0

    code https://godbolt.org/z/vzzbb7Erx

    with 12.1 <= gcc <= 15.3 and O3 and sanitizer enabled
    we are able to get compiler error regarding some memory bug at compile time

**********/

#include <iostream>
#include <memory>

void useit(std::unique_ptr<int> ) {

}

int main() {

    int * ptr = new int{42};
    useit(std::unique_ptr<int>(ptr));
    delete ptr;

    return 0;
}

/*****
    END OF FILE
**********/

