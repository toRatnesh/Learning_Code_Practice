/*****

References
    episode https://www.youtube.com/watch?v=NMWv2vQQjXE
    https://en.cppreference.com/w/cpp/language/pointer

**********/

#include <iostream>
#include <string>
//#include <thread>
//#include <vector>

auto callme(auto callable, auto... args) { return callable(args...); }

auto fun(auto val) { return val; }

std::string getVal(std::string val) { return val; }
int getVal(int val) { return val; }

int main() {

    std::cout << "=== Using Template Function ===\n";

    //std::cout << callme(fun, std::string("sample string")) << '\n';
    std::cout << callme(static_cast<std::string (*)(std::string)>(fun), std::string("calling template function using string")) << '\n';
    std::cout << callme(static_cast<double (*)(double)>(fun), 13.89) << '\n';

    std::cout << "=== Using Overloaded Function ===\n";
    // CE error: no matching function for call to 'callme(<unresolved overloaded function type>, std::string)'
    // std::cout << callme(getVal, std::string("sample string")) << '\n';

    std::cout << callme(static_cast<std::string (*)(std::string)>(getVal), std::string("sample string")) << '\n';
    std::cout << callme(static_cast<int (*)(int)>(getVal), 13) << '\n';

    // CE  error: address of overloaded function 'getVal' cannot be static_cast to type 'double (*)(double)'
    //std::cout << callme(static_cast<double (*)(double)>(getVal), 14.56) << '\n';
    


    std::cout << "=== Using Lambda Function ===\n";
    // ALTERNATIVE IS TO USE LAMBDA, LAMBDA WORK BECAUSE LAMBDA ARE NOT ACTUALLY FUNCTIONS 
    // BUT IT HAS A MEMBER FUNCTION CALL OPERATOR THAT IS TEMPLATE
    std::cout << callme([](auto v){ return getVal(v);}, 23) << '\n';
    std::cout << callme([](auto v){ return getVal(v);}, std::string("using lambda")) << '\n';
    std::cout << callme([](auto v){ return getVal(v);}, 12.98) << '\n';
    std::cout << callme([](auto v){ return getVal(v);}, 'A') << '\n';

    return 0;
}

/*****
    END OF FILE
**********/


