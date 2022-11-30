/********************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

12. Dealing with Strings as Template Parameters

12.1 Using Strings in Templates

    Non-type template parameters can be only constant integral values (including enumerations), pointers
    to objects/functions/members, lvalue references to objects or functions, or std::nullptr_t (the
    type of nullptr).

    For pointers, linkage is required, which means that you can’t pass string literals directly. However,
    since C++17, you can have pointers with internal linkage.

    Since C++17 we may use a compile time function that return the address

*********************/

#include <iostream>
#include <string>

template<const char * str>
auto fun() {
    std::clog << str << '\n';
}

template<const char * str>
class S {
    public:
    void display() {
        std::clog << str << '\n';
    }
    
};

extern char msg[];                              // external linkage
char msg[] = "Non type template pointer in CPP";
char msg11[] = "Non type template pointer in CPP-11";    // internal linkage

constexpr char cmsg[] = "constexpr char array literal";
constexpr const char * fun() {
    return cmsg;
}

int main() {
    std::clog << "=== template function: non type temaplate parameter as pointer" << '\n';
    fun<msg>();
    fun<msg11>();
    static char msg17[] = "Non type template pointer in CPP-17"; 
    // no linkage, CE Before CPP17: error: '& msg17' is not a valid template argument of type 'const char*' because 'msg17' has no linkage
    fun<msg17>();
    
    std::clog << "=== template class: non type temaplate parameter as pointer" << '\n';
    S<msg> m;       m.display();
    S<msg11> m11;   m11.display();
    S<msg17> m17;   m17.display();

    std::clog << "=== using constexpr function pointer return value" << '\n';
    static_assert(fun() == cmsg);
    fun<fun()>();
    S<fun()> f;   f.display();

    return 0;
}

/*************
    END OF FILE
*************/
