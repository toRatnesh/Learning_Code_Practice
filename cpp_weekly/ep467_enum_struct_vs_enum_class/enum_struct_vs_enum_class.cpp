/*****

References
    episode https://www.youtube.com/watch?v=1CjVTCiY4fc
    https://en.cppreference.com/w/cpp/language/enum

    the keywords class and struct are exactly equivalent
    
**********/

#include <iostream>

enum struct XColor {
    RED,
    GREEN,
    BLACK
};

enum class YColor {
    RED,
    GREEN,
    BLACK
};

int main() {

    std::cout << "XColor::RED " << static_cast<int>(XColor::RED) << '\n';
    std::cout << "YColor::GREEN " << static_cast<int>(YColor::GREEN) << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


