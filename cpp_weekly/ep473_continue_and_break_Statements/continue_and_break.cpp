/*****

References
    episode https://www.youtube.com/watch?v=CiB1ex0hi3w
    https://en.cppreference.com/w/cpp/language/continue
    https://en.cppreference.com/w/cpp/language/break


    continue and break statements are code smell and should be avoided

    break should almost always be a return and the loop should me moved 
    into a lambda or a function

**********/

#include <iostream>

int main() {

    auto list = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    
    for(const auto val : list) {
        std::cout << "Value : ";

        if(4 == val) {
            std::cout << '\n';
            continue;
        }
        if(val > 6) {
            break;
        }

        std::cout << val << '\n';
    }

    std::cout << '\n';
    std::cout << '\n';
    auto lambda = [](const auto cont) { 
        for(const auto val : cont) {

            std::cout << "Value : ";

            if(4 == val) {
                std::cout << '\n';
                continue;
            }

            if(val > 6)
            return true;

            std::cout << val << '\n';
        }

        return false;
    };

    auto ret = lambda(list);

    return 0;
}

/*****
    END OF FILE
**********/


