
/*****

References:
    https://www.youtube.com/watch?v=G5ewfxJ0KMU
    https://en.cppreference.com/w/cpp/language/constructor
    https://learn.microsoft.com/en-us/cpp/cpp/delegating-constructors?view=msvc-170

This example demonstrates about C++11 Delegating constructors feature

Delegating constructor
    If the name of the class itself appears as class-or-identifier in the member initializer list, 
    then the list must consist of that one member initializer only; such a constructor is known as the delegating constructor, 
    and the constructor selected by the only member of the initializer list is the target constructor.

    In this case, the target constructor is selected by overload resolution and executed first, 
    then the control returns to the delegating constructor and its body is executed.

    Delegating constructors cannot be recursive.

    The constructor delegation syntax doesn't prevent the accidental creation of constructor recursion.
    It's your responsibility to avoid cycles.

**********/

#include <iostream>
#include <string>

class S {
    std::string     fname;
    std::string     mname;
    std::string     lname;

    public:
    ~S() { std::cout << "~S()\n"; }
    S() { std::cout << "S()\n"; }
    S(std::string fn) : fname{fn} { std::cout << "S(std::string)\n"; }

    // CE  error: an initializer for a delegating constructor must appear alone
    // S(std::string fn, std::string mn) : S(fn), mname{mn} { }

    S(std::string fn, std::string mn) : S(fn) { 
        mname = mn; 
        std::cout << "S(std::string , std::string )\n";
    }
    S(std::string fn, std::string mn, std::string ln) : S(fn, mn) { 
        lname = ln;
        std::cout << "S(std::string , std::string, std::string )\n";
    }

    // RECURSIVE
    //S(std::string , int ival) : S(ival) { }
    // CE error: constructor for 'S' creates a delegation cycle [-Wdelegating-ctor-cycles]
    //S(int ival) : S("recursion", ival) {}

};

int main() {

    { S s; }
    { S s("first"); }
    { S s("first", "middle"); }
    { S s("first", "middle", "last"); }

    return 0;
}

/*****
    END OF FILE
**********/


