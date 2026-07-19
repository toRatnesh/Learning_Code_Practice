/*****

References

	episode https://www.youtube.com/watch?v=ay8BnkWKKWA
    https://en.cppreference.com/cpp/language/range-for

    code https://godbolt.org/z/oqP88dd8o

    Update to C++23 range based for loop

    Temporary range initializer
        If range-initializer returns a temporary, its lifetime is extended until the end of the loop, 
        as indicated by binding to the forwarding reference // range //.

        Lifetimes of all temporaries within range-initializer are not extended unless they would 
        otherwise be destroyed at the end of range-initializer(since C++23).

**********/

#include <iostream>
#include <list>

const std::list<int> &  viewIt(const std::list<int> & data) {
    return data;
}

std::list<int> get() {
    return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

int main() {

    /*
        C++20 extends only the lifetime of the direct object you are getting back.
        The direct object we are getting back from viewIt() here is const reference to something else.
        
        The problem now is the actual value, the actual object that get() produces, 
        it only gets lifetime extended during the call of viewIt();

        Check it in cppinsights https://cppinsights.io/s/5ab7bf26
    */

    {
        // Correct version pre c++23
        for(const auto data = get(); 
            const auto e : viewIt(data)) 
        {   
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }

    
    {

        // wrong pre c++23
        for(auto e : viewIt(get())) // warning: possibly dangling reference to a temporary
        {   
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }


    {
        // wrong pre c++23
        for(const auto e : viewIt(get())) // warning: possibly dangling reference to a temporary
        {   
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }


    return 0;
}

/*****
    END OF FILE
**********/

