/*****

ep054_You_cannot_force_a_move

References

	episode https://www.youtube.com/watch?v=T_Ur97_rVZA
    https://en.cppreference.com/w/cpp/utility/move
    
std::move
    std::move is used to indicate that an object t may be "moved from", 
    i.e. allowing the efficient transfer of resources from t to another object.

    In particular, std::move produces an xvalue expression that identifies its argument t. 
    It is exactly equivalent to a static_cast to an rvalue reference type.

    If condition for move does not fulfill it may fall to copy operation

Return value
    static_cast<typename std::remove_reference<T>::type&&>(t)

**********/

#include <iostream>
#include <string>

class St {
    int     val;
    public:
    
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    
    St(const St & other) : val(other.val) { 
        std::puts("St(const St & other)");
    }
    St & operator=(const St & other) { 
        std::puts("operator=(const St & other)");

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::puts("St(St && other)");
    }
    St & operator=(St && other) { 
        std::puts("operator=(St && other)");

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};

class WithDestructor {
    St val;
    public:
    ~WithDestructor()   = default;
};

class WithoutDestructor {
    St val;
};

int main() {
    {   std::puts("=== Moving object of a class with destructor ===");
        WithDestructor  o1;
        WithDestructor  o2 = std::move(o1); // as user destructor deletes move operation move fallbacks to copy
        // WithDestructor o2 = WithDestructor(static_cast<const WithDestructor &&>(std::move(o1))); // CppInsights
    }

    {   std::puts("\n=== Moving object of a class without destructor ===");
        WithoutDestructor   o1;
        WithoutDestructor   o2 = std::move(o1);
    }

    return 0;
}

/*****
    END OF FILE
**********/

