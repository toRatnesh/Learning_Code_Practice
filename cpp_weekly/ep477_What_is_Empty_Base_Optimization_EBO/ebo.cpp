/*****

References
    episode https://www.youtube.com/watch?v=KU-Ahb86izo
    https://en.cppreference.com/w/cpp/language/ebo
    https://en.cppreference.com/w/cpp/language/attributes/no_unique_address

**********/

#include <iostream>
#include <string>

#define COUT_EXP(exp)  std::cout << #exp << "   " << exp << '\n';

class EmptyBase1 { };

class EmptyBase2 { };

class Base {
    int m; 
};

class EmptyDerived : public EmptyBase1, EmptyBase2 { 
   
};

class Derived : public EmptyBase1, EmptyBase2 { 
    std::string s;
};

class Derived2 : public EmptyBase1, EmptyBase2, Base { 
    int m;
};

class Data {
    EmptyBase1 e1;
    EmptyBase2 e2;   
};

class DataNoUniqueAddress {
    [[no_unique_address]] EmptyBase1 e1;
    [[no_unique_address]] EmptyBase2 e2;   
};

int main() {
    COUT_EXP(sizeof(EmptyBase1));
    COUT_EXP(sizeof(EmptyBase2));
    COUT_EXP(sizeof(Base));
    
    std::cout << '\n';
    
    COUT_EXP(sizeof(EmptyDerived));
    COUT_EXP(sizeof(Derived));
    COUT_EXP(sizeof(Derived2));

    std::cout << '\n';

    COUT_EXP(sizeof(Data));
    COUT_EXP(sizeof(DataNoUniqueAddress));

    return 0;
}

/*****
    END OF FILE
**********/


