
/*****

References
    episode https://www.youtube.com/watch?v=CagZYOdxYcA
    https://isocpp.org/blog/2012/12/you-dont-know-const-and-mutable-herb-sutter
    https://eel.is/c++draft/res.on.data.races#3


This example demonstrates about drawback of mutable 

A C++ standard library function shall not directly or indirectly modify objects 
([intro.multithread]) accessible by threads other than the current thread unless 
the objects are accessed directly or indirectly via the function's non-const arguments, 
including this.

**********/

#include <iostream>
#include <string>
#include <vector>
#include <thread>

class AvoidMutable {
    
    std::string header;
    std::string footer;

    std::string safe_cache{header+footer};  // this will initialize during object creation

    mutable std::string cache;
    mutable bool cache_set = false;

    public:

    AvoidMutable(std::string h, std::string f) 
    : header(h), footer(f) { 

    }

    std::string getHeaderFooter() const {
        // You will need to mutex to make mutable thread safe
        if(not cache_set) {
            cache = header + ", " + footer;
            cache_set = true;
        }
        std::cout << cache << '\n';
        return cache;
    }

    std::string getSafeHeaderFooter() const {
        std::cout << safe_cache << '\n';
        return safe_cache;
    }

};

int main() {
    const AvoidMutable obj("Some large header value on heap", "Some large footer value on heap");

    {
        std::jthread th1(&AvoidMutable::getHeaderFooter, &obj); // pass object by pointer
        std::jthread th2(&AvoidMutable::getHeaderFooter, &obj); // pass object by pointer
    }

    {
        std::jthread th1(&AvoidMutable::getSafeHeaderFooter, &obj); // pass object by pointer
        std::jthread th2(&AvoidMutable::getSafeHeaderFooter, &obj); // pass object by pointer
    }

    return 0;
}

/*****
    END OF FILE
**********/


