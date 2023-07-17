/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/language/alignas
    https://en.cppreference.com/w/cpp/memory/new/align_val_t
    https://en.cppreference.com/w/cpp/memory/c/aligned_alloc

28 new and delete with Over-Aligned Data

    over-aligned types(since C++11), having a bigger alignment than the default alignment

    struct alignas(32) MyType32 {
        int i;
        char c;
        std::string s[4];
    };

    dynamic/heap allocation of over-aligned data is not handled correctly in C++11 and C++14
    operator new for over-aligned types by default ignores the requested alignment, so that a type usually 63-bytes aligned might, for example, only be 8-bytes or 16-bytes aligned

    this issue has been solved in C++17, that new overloads with an alignment argument are provided

28.2 Implementing operator new() for Aligned Memory

    28.2.1 Implementing Aligned Allocation Before C++17
        Before C++17, a requested alignment was not automatically passed to these functions and the default mechanisms allocated dynamic memory without considering the alignment.
        Even worse, there was no portable way to perform the request for over-aligned dynamic memory.
        You should always replace both the unsized and the sized overload of operator delete() since C++14. Letting one calling the other usually is fine.
        
*************/

#include <iostream>
#include <cstdlib>

struct alignas(32) AlignedData {

    int     idata;
    char    cdata;

    static void * operator new(std::size_t mem_size) {
        printf("new(std::size_t)\n");
        return aligned_alloc(alignof(AlignedData), mem_size);
    }

    static void operator delete(void * ptr) {
        printf("delete(void *)\n");
        std::free(ptr);
        ptr = nullptr;
        return ;
    }

    static void operator delete(void * ptr, std::size_t ) {
        printf("delete(void *, std::size_t)\n");
        return delete(ptr);
    }

};

int main() {

    {
        auto    ptr = new AlignedData;
        delete  ptr;    ptr= nullptr;
    }

    {
        auto    ptr = new AlignedData{36, 'A'};
        delete  ptr;    ptr= nullptr;
    }

    return 0;
}

/**********
    END OF FILE
*************/


