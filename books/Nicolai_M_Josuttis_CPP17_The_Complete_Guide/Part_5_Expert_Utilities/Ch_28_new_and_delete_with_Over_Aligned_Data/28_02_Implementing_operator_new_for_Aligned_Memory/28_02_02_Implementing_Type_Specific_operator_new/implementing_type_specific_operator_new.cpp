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

    28.2.2 Implementing Type-Specific operator new()
    Since C++17, there is now support for over-aligned data.
    All allocation functions take the alignment parameter as type size_t, which means that we have to use the static cast to convert the value from type std::align_val_t.


    When is operator new() Called?
        version with only the size argument, provided for requests of default-aligned data. However, it can also serve as fallback, if a version for over-aligned data is not provided.
        version with the additional align argument, provided for requests of over-aligned data.

        Which overload is used does not necessarily depend on whether alignas is used. 
        It depends on the platform-specific definition of over-aligned data.

        A compiler switches from default to over alignment,  with any alignment larger than __STDCPP_DEFAULT_NEW_ALIGNMENT__, a call of new switches from trying to call
            operator new(std::size_t)
        to a trial to call
            operator new(std::size_t, std::align_val_t)

    Type-Specific Fallbacks
        If the std::align_val_t overloads are not provided for a type-specific operator new(), the overloads without this argument are used as fallbacks.
        The opposite is not true. If a type only provides the overloads with the alignment parameter, any trial to allocate storage with new using the default alignment will fail.

        It would also be an error, if for the type an alignment is requested that is (less than) the default alignment.

    Requesting an Alignment in the new expression

    If you pass an requested alignment in the new expression, the passed alignment argument is always passed and has to be supported by the operator new().
    Thus, a call such as:
        std::string* p = new(std::align_val_t{64}) std::string; // 64-bytes aligned
    will always try to call:
        operator new(std::size_t, std::align_val_t)
    A size-only overload would not serve as a fallback here.

    For a specific alignment request for an over-aligned type, for example, you call:
        MyType32* p = new(std::align_val_t{64}) MyType32{};
    and MyType32 is over-aligned, the compiler first tries to call
        operator new(std::size_t, std::align_val_t, std::align_val_t)
    with 32 as the second argument (the general over-alignment of the type) and 64 as third argument (the requested specific alignment). 
    Only as a fallback,  
        operator new(std::size_t, std::align_val_t)  
    is called with 64 as the requested specific alignment.

*************/

#include <iostream>
#include <cstdlib>
#include <new>

struct alignas(32) AlignedData {

    int     idata;
    char    cdata;

    static void * operator new(std::size_t mem_size) {
        printf("new(std::size_t) size %zu\n", mem_size);
        return ::operator new(mem_size);
    }

    static void * operator new(std::size_t mem_size, std::align_val_t align) {
        printf("new(std::size_t, std::align_val_t) size %zu align %zu\n", mem_size, static_cast<std::size_t>(align));
        return ::operator new(mem_size, align);
    }

    static void operator delete(void * ptr) {
        printf("delete(void *)\n");
        return ::operator delete(ptr);
    }

    static void operator delete(void * ptr, std::size_t mem_size) {
        printf("delete(void *, std::size_t) size %zu\n", mem_size);
        return AlignedData::operator delete(ptr);
    }

    static void operator delete(void * ptr, std::align_val_t align) {
        printf("delete(void *, std::align_val_t) align %zu\n", static_cast<std::size_t>(align));
        return ::operator delete(ptr, align);
    }

    static void operator delete(void * ptr, std::size_t mem_size, std::align_val_t align) {
        printf("delete(void *, std::size_t, std::align_val_t) size %zu align %zu\n", mem_size, static_cast<std::size_t>(align));
        return AlignedData::operator delete(ptr, align);
    }

};

int main() {

    {
        std::cout << "=== without alignment in new expression ===\n";
        auto    ptr1 = new AlignedData;
        delete  ptr1;    ptr1= nullptr;

        auto    ptr2 = new AlignedData{36, 'A'};
        delete  ptr2;    ptr2= nullptr;
    }


    {
        std::cout << "=== with alignment in new expression ===\n";
        
        // alignment in the new expression, A size-only overload would not serve as a fallback here
        
        auto    ptr1 = new(std::align_val_t{64}) AlignedData;
        delete  ptr1;    ptr1= nullptr;

        auto    ptr2 = new(std::align_val_t{64}) AlignedData{36, 'A'};
        delete  ptr2;    ptr2= nullptr;
    }

    return 0;
}

/**********
    END OF FILE
*************/


