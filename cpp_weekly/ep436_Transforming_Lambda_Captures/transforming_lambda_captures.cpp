/*****

ep436_Transforming_Lambda_Captures

References
episode https://www.youtube.com/watch?v=t6hFPKiOS-Q
https://en.cppreference.com/w/cpp/language/lambda


This example demonstrates about transforming lambda capture

**********/

#include <print>
#include <string>
#include <string_view>

template<typename ... StringLIke>
void processStringLike(const StringLIke & ... data) {

/*     
    // CE error: request for member 'size' in 'data#0', which is of non-class type 'const char [11]'
    auto display = [&](){
        ((std::println("{} {}", data.size(), data)), ...);
    };

 */

    auto display = [... data = std::string_view{data}](){
        ((std::println("{} {}", data.size(), data)), ...);
    };

    display();
}

int main() {

    processStringLike("Char array", std::string("a string"), std::string_view("a string view"));

    return 0;
}

/*****
    END OF FILE
**********/


