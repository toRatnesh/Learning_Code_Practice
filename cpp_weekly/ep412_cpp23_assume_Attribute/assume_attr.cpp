/*****

    This example demonstrates about C++23 [[assume]] attribute

    The purpose of an assumption is to allow compiler optimizations based on the information given.

    For more info visit
    episode https://www.youtube.com/watch?v=Frl8XKhvA4Q
    https://en.cppreference.com/w/cpp/language/attributes/assume

**********/

#include <iostream>
#include <string>
#include <exception>

int * get_ptr(bool flag) {
    int * ptr = nullptr;
    if(flag) {
        ptr = new int(5);
    }
    return ptr;
}

int get_val(int * ptr) {

    if(! ptr) {
        throw std::string("Pointer is null");
    }
    return *ptr;
}

int main() {
    {
        int * ptr = get_ptr(true);
        [[assume(ptr != nullptr)]];
        int val = get_val(ptr);
        std::cout << "value is " << val << '\n';
	delete ptr;
	ptr = nullptr;
    }
    
    return 0;
}


/*****
    END OF FILE
**********/


