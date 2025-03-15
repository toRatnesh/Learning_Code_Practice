/*****

References

    episode https://www.youtube.com/watch?v=GyAZg1LfPZo
    https://en.cppreference.com/w/cpp/utility/functional/invoke

    std::invoke_r only works with impicit conversions and we don't like implicit conversions

**********/

#include <print>
#include <functional>
#include <string>
#include <string_view>

int get_ivalue(const int input) { return input + 20; }
float get_fvalue(const float input) { return input + 20.5f; }

std::string_view get_sv() { return "sample string view"; }
std::string get_str() { return "sample string"; }

int main() {
    std::println("=== using std::invoke ===");
    std::print("{}, ", std::invoke(get_ivalue, 10));
    std::print("{}, ", std::invoke(get_fvalue, 10.5));
    std::print("{}, ", std::invoke(get_sv));
    std::println("{}", std::invoke(get_str));
    
    std::println("=== using std::invoke_r with same return type ===");
    std::print("{}, ", std::invoke_r<int>(get_ivalue, 10));
    std::print("{}, ", std::invoke_r<float>(get_fvalue, 10.5));
    std::print("{}, ", std::invoke_r<std::string_view>(get_sv));
    std::println("{}", std::invoke_r<std::string>(get_str));
    
    std::println("=== using std::invoke_r with convertable return type ===");
    // gcc and clang both exclude the stdlib from warnings to see it use -Wsystem-headers 
    std::print("{}, ", std::invoke_r<float>(get_ivalue, 10));
    std::print("{}, ", std::invoke_r<int>(get_fvalue, 10.5));
    //std::print("{}, ", std::invoke_r<std::string>(get_sv)); // CE no implicit conversion from string_view to string
    std::print("{}, ", std::string{std::invoke(get_sv)});
    //std::println("{}", std::invoke_r<std::string_view>(get_str)); // RUNTIME ERROR
    std::println("{}", std::string_view{std::invoke(get_str)});
    
    return 0;
}

/*****
    END OF FILE
**********/

