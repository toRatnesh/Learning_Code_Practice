/***********

    This example demonstrates better alternative for pointer arithmetic

    For more info visit:
    episode https://www.youtube.com/watch?v=YahYVRS1Ktg

****************/

#include <iostream>
#include <vector>
#include <cstring>
#include <span>
#include <ranges>

void fun(const char * msg, const std::size_t msg_size) {
    
    {   // pointer arithmetic
        const std::vector<char> lmsg(msg, msg+msg_size);
        for(const auto & elem : lmsg) {
            std::cout << elem;
        }
        std::cout << '\n';
    }

    {   // option - 1
        std::vector<char> const lmsg(msg, std::next(msg, static_cast<ptrdiff_t>(msg_size)));
        for(const auto & elem : lmsg) {
            std::cout << elem;
        }
        std::cout << '\n';
    }

    {   // option - 2
        for(const auto & elem : std::span<char const>(msg, msg_size)) {
            std::cout << elem;
        }
        std::cout << '\n';
    }
    
    {
        for(const auto & elem : std::span<char const>(msg, msg_size) | std::ranges::views::drop(2)) {
            std::cout << elem;
        }
        std::cout << '\n';
    }    

    {
        for(const auto & elem : std::span<char const>(msg, msg_size).subspan(3)) {
            std::cout << elem;
        }
        std::cout << '\n';
    }

    return ;
}

int main() {
    const char * msg = "simple string";
    fun(msg, strlen(msg));

    return 0;
}

/***********
    END OF FILE
****************/





