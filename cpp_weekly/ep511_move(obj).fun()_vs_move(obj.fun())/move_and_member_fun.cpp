/*****

ep511_move(obj).fun()_vs_move(obj.fun())

References:
    episode     https://www.youtube.com/watch?v=nLjrMcjsa0Y
    https://en.cppreference.com/w/cpp/utility/move.html

std::move
    std::move is used to indicate that an object t may be "moved from", 
    i.e. allowing the efficient transfer of resources from t to another object.
    
    In particular, std::move produces an xvalue expression that identifies its argument t.
    It is exactly equivalent to a static_cast to an rvalue reference type.

move(obj).fun()
    calls member function fun() on an rvalue qualified object i.e. calls an && qualified member function if it exists


move(obj.fun())
    casts return value of member function fun() to an rvalue

**********/

#include <iostream>
#include <format>
#include <memory>
#include <string>

class S {
    public:
    S() { std::cout << "default cx\n"; }

    S(const S &) { std::cout << "copy cx\n"; }
    S(S &&) { std::cout << "move cx\n"; }

    S& operator=(const S &) { std::cout << "copy =\n"; return *this; }
    S& operator=(S &&) { std::cout << "move =\n"; return *this; }

};

std::ostream & operator<<(std::ostream & os, const S &) {
    os << "s_value\n";
    return os;
}

class Test {
    S m_data;

    public:
    explicit Test(S data) : m_data{data} {}

    S test() & {
        std::cout << "Test::test() &" << '\n';
        return m_data;
    }

    S test() const & {
        std::cout << "Test::test() const &" << '\n';
        return m_data;
    }

    S test() && {
        std::cout << "Test::test() &&" << '\n';
        return std::move(m_data);
    }

    S test() const && {
        std::cout << "Test::test() const &&" << '\n';
        return std::move(m_data);
    }

};


int main()
{
    {
        Test t(S{});
        auto val = std::move(t).test();
        std::cout << "value: " << val << '\n';
    }

    {
        auto val = Test{S{}}.test();
        std::cout << "value: " << val << '\n';
    }
    
    {
        Test t(S{});
        auto val = std::move(t.test());
        std::cout << "value: " << val << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/

