/*****

References
    episode:    https://www.youtube.com/watch?v=JtFVyXQ00PQ
    https://en.cppreference.com/w/cpp/language/reinterpret_cast.html
    https://en.cppreference.com/w/cpp/memory/start_lifetime_as.html

**********/

#include <iostream>
#include <format>
#include <memory>

void use_reinterpret_cast() {

    std::cout << std::format("=== {} ===\n", __func__);

    int * pi = new int{12};
    std::cout << std::format("*pi: {}\n", *pi);

    float * pf = reinterpret_cast<float *>(pi);
    std::cout << std::format("*pf: {}\n", *pf);

    int ival = static_cast<int>(*pf);
    std::cout << std::format("ival: {}\n", ival);

    int * pi2 = reinterpret_cast<int *>(pf);
    std::cout << std::format("*pi2: {}\n", *pi2);

    if(pi) {
        delete pi;
        pi = nullptr;
    }

}

void use_start_lifetime_as() {

    std::cout << std::format("=== {} ===\n", __func__);

    int * pi = new int{12};
    std::cout << std::format("*pi: {}\n", *pi);

    float * pf = std::start_lifetime_as<float>(pi);
    std::cout << std::format("*pf: {}\n", *pf);

    int ival = static_cast<int>(*pf);
    std::cout << std::format("ival: {}\n", ival);

    int * pi2 = std::start_lifetime_as<int>(pf);
    std::cout << std::format("*pi2: {}\n", *pi2);

    if(pi) {
        delete pi;
        pi = nullptr;
    }

}

int main()
{
    use_reinterpret_cast();

    use_start_lifetime_as();
    
    return 0;
}

/*****
    END OF FILE
**********/

