/*****

References
    episode https://www.youtube.com/watch?v=AFcfRf5KWe0
    https://en.cppreference.com/w/cpp/utility/forward_like

std::forward_like

    template< class T, class U >
    constexpr auto&& forward_like( U&& x ) noexcept;    (since C++23)

    Returns a reference to x which has similar properties to T&&.

**********/

#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

class Person {
    std::string m_name;

    public:
    /*
    //std::string get_name()      { return m_name; }  // CE: can't be overloaded with get_name() &
    std::string get_name() &        { std::puts("get_name() &"); return m_name; }
    std::string get_name() &&       { std::puts("get_name() &&"); return m_name; }
    
    std::string get_name() const &        { std::puts("get_name() const &"); return m_name; }
    std::string get_name() const &&       { std::puts("get_name() const &&"); return m_name; }
    */
    auto && get_name(this auto && self) {
        return std::forward_like<decltype(self)>(self.m_name);
    }
};

Person get_person() { return Person{}; }
const Person get_person_const() { return Person{}; }

template<typename T>
concept is_const_lvalue_reference_v = std::is_lvalue_reference_v<T> and std::is_const_v<std::remove_reference_t<T>>;

template<typename T>
concept is_const_rvalue_reference_v = std::is_rvalue_reference_v<T> and std::is_const_v<std::remove_reference_t<T>>;


int main() {

    {
        Person p;
        std::cout << std::boolalpha 
        << "std::is_lvalue_reference_v<decltype(p.get_name())> " << std::is_lvalue_reference_v<decltype(p.get_name())> << '\n'
        << "is_const_lvalue_reference_v<decltype(p.get_name())> " << is_const_lvalue_reference_v<decltype(p.get_name())> << '\n' 

        << "std::is_rvalue_reference_v<decltype(std::move(p.get_name()))> " << std::is_rvalue_reference_v<decltype(std::move(p.get_name()))> << '\n'
        << "is_const_rvalue_reference_v<decltype(std::move(p.get_name()))> " << is_const_rvalue_reference_v<decltype(std::move(p.get_name()))> << '\n';    

    }
    std::cout << '\n';
    
    {
        const Person p;
        std::cout << std::boolalpha 
        << "std::is_lvalue_reference_v<decltype(p.get_name())> " << std::is_lvalue_reference_v<decltype(p.get_name())> << '\n'
        << "is_const_lvalue_reference_v<decltype(p.get_name())> " << is_const_lvalue_reference_v<decltype(p.get_name())> << '\n' 

        << "std::is_rvalue_reference_v<decltype(std::move(p.get_name()))> " << std::is_rvalue_reference_v<decltype(std::move(p.get_name()))> << '\n'
        << "is_const_rvalue_reference_v<decltype(std::move(p.get_name()))> " << is_const_rvalue_reference_v<decltype(std::move(p.get_name()))> << '\n';    
        
    }
    std::cout << '\n';

    {
        std::cout << std::boolalpha 
        << "std::is_lvalue_reference_v<decltype(get_person().get_name())> " << std::is_lvalue_reference_v<decltype(get_person().get_name())> << '\n'
        << "is_const_lvalue_reference_v<decltype(get_person().get_name())> " << is_const_lvalue_reference_v<decltype(get_person().get_name())> << '\n' 

        << "std::is_rvalue_reference_v<decltype(std::move(get_person().get_name()))> " << std::is_rvalue_reference_v<decltype(std::move(get_person().get_name()))> << '\n'
        << "is_const_rvalue_reference_v<decltype(std::move(get_person().get_name()))> " << is_const_rvalue_reference_v<decltype(std::move(get_person().get_name()))> << '\n';
        
    }
    std::cout << '\n';

    {
        std::cout << std::boolalpha 
        << "std::is_lvalue_reference_v<decltype(get_person_const().get_name())> " << std::is_lvalue_reference_v<decltype(get_person_const().get_name())> << '\n'
        << "is_const_lvalue_reference_v<decltype(get_person_const().get_name())> " << is_const_lvalue_reference_v<decltype(get_person_const().get_name())> << '\n' 

        << "std::is_rvalue_reference_v<decltype(std::move(get_person_const().get_name()))> " << std::is_rvalue_reference_v<decltype(std::move(get_person_const().get_name()))> << '\n'
        << "is_const_rvalue_reference_v<decltype(std::move(get_person_const().get_name()))> " << is_const_rvalue_reference_v<decltype(std::move(get_person_const().get_name()))> << '\n';
        
    }

    return 0;
}

/*****
    END OF FILE
**********/


