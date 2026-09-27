/*****

References:
    episode     https://www.youtube.com/watch?v=cXjY5fWUv7g
    code        https://godbolt.org/z/v597xrbMj

    This example demonstrates about impact of static const

    we should prefer static constexpr 
    
    static const is a code smell 
    and since c+11 auto (local) varible are use guard for MT-safe

**********/

#include <iostream>
#include <string_view>


static const std::string str{"static const is guarded"};

int main() {

    {
        // since C++11 local static is guraded by mutex
        static const std::string str{"static const is guarded"};
    }

    {
        static constexpr std::string_view str{"static constexpr is not guarded and initialized with const value"};
        //str = "this varible is not mutable";
    }


    {
        static constinit std::string_view str{"static constinit is not guarded and initialized with const value but varible is mutable"};
        str = "this is not const and can be mutated";
    }

    {
        static constinit const std::string_view str{"static constinit is not guarded and making it const also makes varible immutable"};
        //str = "this is const and can not be mutated";
    }

    return 0;
}

/*****
    END OF FILE
**********/

