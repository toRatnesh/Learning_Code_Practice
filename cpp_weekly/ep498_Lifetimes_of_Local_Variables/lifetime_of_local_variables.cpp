/*****

References
    episode:    https://www.youtube.com/watch?v=F-gRrU-g22k
    scope https://en.cppreference.com/w/cpp/language/scope.html

    In this example we will demonstrate about Lifetime of local variables

**********/

#include <iostream>
#include <string>
#include <print>

class St {
    int id;

   public:
    ~St() { std::println("dx {}", id); }
    St(int id) : id{id} { std::println("cx {}", id); }

    St(const St& other) : id(other.id) { std::println("copy cx {}", id); }
    St& operator=(const St& other) {
        std::println("copy = {}", id);

        if (this != &other) {
            id = other.id;
        }
        return *this;
    }

    St(St&& other) : id(std::move(other.id)) { std::println("move cx {}", id); }
    St& operator=(St&& other) {
        std::println("move = {}", id);

        if (this != &other) {
            id = std::move(other.id);
        }
        return *this;
    }
};


auto make_st(const bool flag) {
    if(flag) {
        return St{0};
    }

    St s{0};
    return s;
}

auto get_st(const bool flag) {
    return make_st(flag);
}

int main() { 

    St st_1{1};    // scope of st_1 starts

    {
        St st_2{2};    // scope of st_2 starts
        
        {
            St st_1{3};    // scope of st_1 starts and hides the outer st_1

        }   // scope of st_1 ends

    }   // scope of st_2 ends

    {
        St st_3{st_1};
        St st_4{std::move(st_3)};
    }

    std::println("=== check RVO ==="); 
    {
        auto val = get_st(true);
    }

    {
        auto val = get_st(false);
    }   
    std::println("======");  

    return 0; 
}   // scope of st_1 ends

/*****
    END OF FILE
**********/
