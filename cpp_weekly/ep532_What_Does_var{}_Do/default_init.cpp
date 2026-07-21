/*****

References:
    episode     https://www.youtube.com/watch?v=A3Kr6Q4bIZs
    https://en.cppreference.com/cpp/language/default_constructor
    C++ Insights ep069_default_and_uniform_initialization_Best_Practice_Explained
    https://github.com/toRatnesh/Learning_Code_Practice/blob/main/cpp_insights/ep069_default_and_uniform_initialization_Best_Practice_Explained/default_and_uniform_initialization.cpp

    code https://godbolt.org/z/fcvoEeecb

    This example demonstrates about default initialization with default constructor and {}

**********/

#include <iostream>
#include <string>

class Student {
    std::string     m_name;
    int             m_age;

    public:

    Student() = default;

    std::string name()  const { return m_name; }
    int         age()   const { return m_age; }
};

int main()
{
    {
        Student     st;     // Student's member may be uninitialized
        std::cout << "name " << st.name() << ", age " << st.age() << '\n';
        //return st.age();
    }

    {
        Student     st{};   // Student's member is initialized, because Implicitly-defined default constructor initializes all members
        std::cout << "name " << st.name() << ", age " << st.age() << '\n';
        //return st.age();
    }

    return 0;
}

/*****
    END OF FILE
**********/

