/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/language/alignas
    https://en.cppreference.com/w/cpp/memory/new/align_val_t
    https://en.cppreference.com/w/cpp/memory/new/operator_new

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

28.3 Implementing Global operator new()
	C++ now provide a significant number of global overloads for operator new() and delete()
	For your own implementation you don’t have to override them all, It is enough to implement the following basic functions

	void* ::operator new(std::size_t);
	void* ::operator new(std::size_t, std::align_val_t);

	void ::operator delete(void*) noexcept;
	void ::operator delete(void*, std::size_t) noexcept;
	void ::operator delete(void*, std::align_val_t) noexcept;
	void ::operator delete(void*, std::size_t, std::align_val_t) noexcept;

	In principle, the default of the sized versions of operator delete() also just call the unsized versions. 
	However, this might change in future, therefore it is required that you implement both.

28.3.1 Backward Incompatibilities

	Since C++17, the default overload the over aligned data
		::operator new(size_t, align_val_t)
	is called. This is applicable for only global operator new().


	For the type specific operator new(), the operator 
		::operator new(size_t)
	is still also used as a fallback for over-aligned data so that such a program behaves as before C++17.

*************/

#include <iostream>

namespace nonstd{
    void * allocate(std::size_t mem_size, std::size_t align, const char * msg) {
        void * p = nullptr;
        if(0 == align) {
            p = std::malloc(mem_size);
        } else {
            p = std::aligned_alloc(align, mem_size);
        }
        printf("%s with size %zu and align %zu\n", msg, mem_size, align);
        return p;
    }
    void deallocate(void * ptr, std::size_t mem_size, std::size_t align, const char * msg) {
        printf("%s with size %zu and align %zu\n", msg, mem_size, align);
        std::free(ptr);
        ptr = nullptr;
        return ;
    }
}

void * operator new(std::size_t mem_size) {
    return nonstd::allocate(mem_size, 0, "new(std::size_t)");
}

void * operator new(std::size_t mem_size, std::align_val_t align) {
    return nonstd::allocate(mem_size, static_cast<std::size_t>(align), "new(std::size_t, std::align_val_t)");
}


void operator delete(void * ptr) {
    return nonstd::deallocate(ptr, 0, 0, "delete(void *)");
}

void operator delete(void * ptr, std::size_t mem_size) {
    return nonstd::deallocate(ptr, mem_size, 0, "delete(void *, std::size_t)");
}

void operator delete(void * ptr, std::align_val_t align) {
    return nonstd::deallocate(ptr, 0, static_cast<std::size_t>(align), "delete(void *, std::align_val_t)");
}

void operator delete(void * ptr, std::size_t mem_size, std::align_val_t align) {
    return nonstd::deallocate(ptr, mem_size, static_cast<std::size_t>(align), "delete(void *, std::size_t, std::align_val_t)");
}

int main() {
    {
        std::string str1;
        std::string str2     = "This is a sample string which is long enought to require memory allocation";
    }

    {
        std::cout << "=== new ===\n";
        auto    pstr1   = new std::string;
        delete  pstr1;   pstr1 = nullptr;

        auto    pstr3   = new std::string("This string is allocated using new");
        delete  pstr3;   pstr3 = nullptr;

        auto    pstr2   = new(std::align_val_t{64}) std::string;
        delete  pstr2;   pstr2 = nullptr;

        auto    pstr4   = new(std::align_val_t{64}) std::string("This string is aligned allocated using new");
        delete  pstr4;   pstr4 = nullptr;
    }

    {
        std::cout << "=== new[] ===\n";
        auto    pstr1   = new std::string[4];
        delete[]  pstr1;  pstr1=nullptr;

        auto    pstr3   = new std::string[4] {"sample-1", "sample-2 will require heap allocation because its large in size", "sample-3", "sample-4"};
        delete[]  pstr3;  pstr3=nullptr;

        auto    pstr2   = new(std::align_val_t{64}) std::string[4];
        delete[]  pstr2;  pstr2=nullptr;

        auto    pstr4   = new(std::align_val_t{64}) std::string[4] {"aligned sample-1", "aligned sample-2 will require heap allocation because its large in size", "aligned sample-3", "aligned sample-4"};
        delete[]  pstr4;  pstr4=nullptr;
    }



    {
        std::cout << "=== new for aligned struct ===\n";

        struct alignas(32) AlignedData {
            int     offer;
            double  price;

            /* ::operator new(size_t) IS NOT WORKING AS FALLBACK AS MENTIONED IN THEORY

            void * operator new(std::size_t mem_size) {
                return nonstd::allocate(mem_size, 0, "new(std::size_t)");
            }

            void * operator new(std::size_t mem_size, std::align_val_t align) {
                return nonstd::allocate(mem_size, static_cast<std::size_t>(align), "new(std::size_t, std::align_val_t)");
            }

            void operator delete(void * ptr, std::size_t mem_size, std::align_val_t align) {
                return nonstd::deallocate(ptr, mem_size, static_cast<std::size_t>(align), "delete(void *, std::size_t, std::align_val_t)");
            } 
            */           
        };

        auto ptr1 = new AlignedData;
        delete ptr1; ptr1= nullptr;

        auto ptr2 = new(std::align_val_t{64}) AlignedData;
        delete ptr2; ptr2= nullptr;

        auto ptr3 = new(std::align_val_t{4}) AlignedData;
        delete ptr3; ptr3= nullptr;        
    }    

    return 0;
}

/**********
    END OF FILE
*************/


