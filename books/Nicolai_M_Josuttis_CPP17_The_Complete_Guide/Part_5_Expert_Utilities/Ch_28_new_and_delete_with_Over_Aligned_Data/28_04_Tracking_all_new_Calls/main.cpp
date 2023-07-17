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

28.4 Tracking all ::new Calls
	By Overloading new and delete

*************/

#include <iostream>
#include "track_new.hpp"

struct alignas(32) AlignedData {
    int     offer;
    double  price;
};

int main() {

    TrackNew::trace(true);
    TrackNew::reset();
    {
        std::string str1;
        std::string str2     = "This is a sample string which is long enought to require memory allocation";
        TrackNew::status();
    }
    

    {
        auto    pstr1   = new std::string;
        auto    pstr3   = new std::string("This string is allocated using new");
        
        auto    pstr2   = new(std::align_val_t{64}) std::string;
        auto    pstr4   = new(std::align_val_t{64}) std::string("This string is aligned allocated using new");
        TrackNew::status();
        delete  pstr1;   pstr1 = nullptr;
        delete  pstr2;   pstr2 = nullptr;
        delete  pstr3;   pstr3 = nullptr;
        delete  pstr4;   pstr4 = nullptr;
    }
    
    {
        auto    pstr1   = new std::string[4];
        auto    pstr3   = new std::string[4] {"sample-1", "sample-2", "sample-3", "sample-4"};

        auto    pstr2   = new(std::align_val_t{64}) std::string[4];
        auto    pstr4   = new(std::align_val_t{64}) std::string[4] {"aligned sample-1", "aligned sample-2", "aligned sample-3", "aligned sample-4"};
        TrackNew::status();
        delete[]  pstr1;  pstr1=nullptr;
        delete[]  pstr2;  pstr2=nullptr;
        delete[]  pstr3;  pstr3=nullptr;
        delete[]  pstr4;  pstr4=nullptr;
    }

    {
        auto ptr1 = new AlignedData;
        auto ptr2 = new(std::align_val_t{64}) AlignedData;
        auto ptr3 = new(std::align_val_t{4}) AlignedData;
        TrackNew::status();
        delete ptr1; ptr1= nullptr;
        delete ptr2; ptr2= nullptr;
        delete ptr3; ptr3= nullptr;        
    }

    return 0;   
}

/**********
    END OF FILE
*************/


