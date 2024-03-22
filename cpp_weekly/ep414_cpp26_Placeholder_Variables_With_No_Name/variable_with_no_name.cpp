/*****

    when _ is used as the identifier for the declaration of a variable, 
    non static class member variable, lambda capture or structured binding
    
    the introduced name is implicitly given the [[maybe_unused]] attribute

    For more info visit
    episode https://www.youtube.com/watch?v=OZ1gNuF60BU
    https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2169r4.pdf

**********/

#include <print>

class S {
    int m_i;
    public:
    S(int i) : m_i(i) { std::println("S({})", m_i); }
    ~S() { std::println("~S({})", m_i); }
};

int main() {

    int _       = 3;
    double _    = 5.6;

    S _{1};
    {
        S _{2};
    }
    S _{3};

    return 0;
}

/*****
    END OF FILE
**********/


