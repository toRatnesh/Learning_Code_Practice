/*****

References
    episode https://www.youtube.com/watch?v=iUcS0LCj2Ko
    https://en.cppreference.com/w/cpp/utility/tuple/ignore.html
    https://en.cppreference.com/w/cpp/language/attributes/maybe_unused.html
    https://en.cppreference.com/w/cpp/language/conflicting_declarations.html#Potentially-conflict_declarations

_ vs std::ignore vs [[maybe_unused]]

std::ignore:
  * C++11
  * cannot ignore only part
  * return value destroyed immediately
  * might have compile time and debug time overhead

[[maybe_unused]]: 
  * C++17
  * cannot ignore only part
  * must use meaningful name
  * return value lives for rest of scope

_ :
  * C++26
  * can ignore only part!
  * multiple unreachable variables with the
    same name
  * return value lives for rest of scope
  * great for structured bindings!

**********/

#include <print>
#include <string>
#include <tuple>


auto getVal() {
    return std::tuple{"string-1", "string-2", "string-3"};
}

int main() {

    {
        auto [a, b, c] = getVal();
        std::println("{} {} {}", a, b, c);
    }

    {
        auto [a, b, c] = getVal();
        std::println("{} {}", a, b);
    }

    {
        [[maybe_unused]] auto [a, b, c] = getVal();
        std::println("{} {}", a, b);
    }

    {
        std::ignore = getVal();
    }


    {
        auto [_, b, _] = getVal();
        std::println("{}", b);
    }

    return 0;
}

/*****
    END OF FILE
**********/
