/*******

    This example demonstrates about C++23 
    out_ptr and inout_ptr 
    which exist for compatibility between C++ smart pointers and C APIs

    out_ptr: Returns an std::out_ptr_t with deduced template arguments that captures arguments for resetting by reference
    inout_ptr:  Returns an inout_ptr_t with deduced template arguments that captures arguments for resetting by reference.

    For more  ino visit
    episode: https://www.youtube.com/watch?v=DHKoN6ZBrkA
    https://en.cppreference.com/w/cpp/memory/out_ptr_t/out_ptr
    https://en.cppreference.com/w/cpp/memory/out_ptr_t

    https://en.cppreference.com/w/cpp/memory/inout_ptr_t/inout_ptr

**********/

#include <iostream>
#include <cstdio>
#include <memory>

extern "C" {
    void get_data(int ** ptr) {
        int * result = (int *)malloc(sizeof(int));
        *result = 56;
        *ptr = result;
    }

    void use_data(int * ptr) {
        printf("*ptr: %d", *ptr);
    }
}

int main() {
    /*
    out_ptr destructor reset the adapted smart pointer
    https://en.cppreference.com/w/cpp/memory/out_ptr_t
    
    this will lead to UB because calling malloc and then deleting it
    we should pass a smart pointer which know how to free it
    std::unique_ptr<int> data = std::make_unique<int>(34);
    */
    
    /*
    this does not work well as
    std::unique_ptr<int, decltype(free)> data(nullptr, &free);
    */
    
    // using C++20 default constructible lambda
    std::unique_ptr<int, decltype([](int * ptr){ free(ptr); ptr=nullptr;})> data;
    std::cout << "data: " << *data << '\n';

    get_data(std::out_ptr(data));
    std::cout << "data: " << *data << '\n';

    return 0;
}

/*******
    END OF FILE
**********/



