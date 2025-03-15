/*****

References
    episode https://www.youtube.com/watch?v=5ELoDcqqyX4
    Member functions with ref-qualifier https://en.cppreference.com/w/cpp/language/member_functions
    https://www.learncpp.com/cpp-tutorial/ref-qualifiers/

An implicit object member function can be declared with no ref-qualifier, with an lvalue ref-qualifier or the rvalue ref-qualifier. 
During overload resolution, an implicit object member function with a cv-qualifier sequence of class X is treated as follows:

no ref-qualifier: the implicit object parameter has type lvalue reference to cv-qualified X and is additionally allowed to bind rvalue implied object argument
lvalue ref-qualifier: the implicit object parameter has type lvalue reference to cv-qualified X
rvalue ref-qualifier: the implicit object parameter has type rvalue reference to cv-qualified X

**********/

#include <iostream>
#include <string>

class Person {
    std::string m_name;

    public:
    //std::string get_name()      { return m_name; }  // CE: can't be overloaded with get_name() &
    std::string get_name() &        { std::puts("get_name() &"); return m_name; }
    std::string get_name() &&       { std::puts("get_name() &&"); return m_name; }
    
    std::string get_name() const &        { std::puts("get_name() const &"); return m_name; }
    std::string get_name() const &&       { std::puts("get_name() const &&"); return m_name; }
};

Person get_person() { return Person{}; }
const Person get_person_const() { return Person{}; }

int main() {
    {
        Person p;
        p.get_name();
        std::move(p).get_name();
    }
    std::puts("");
    
    {
        const Person p;
        p.get_name();
        std::move(p).get_name();
    }
    std::puts("");

    {
        get_person().get_name();
        std::move(get_person()).get_name();
    }
    std::puts("");

    {
        get_person_const().get_name();
        std::move(get_person_const()).get_name();
    }

    return 0;
}

/*****
    END OF FILE
**********/


