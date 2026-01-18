/*****

References
    episode:    https://www.youtube.com/watch?v=nLjrMcjsa0Y

move(obj).fun()
    obj is moved to fun i.e. obj ownership is transferred
move(obj.fun())
    return vaulue of fun is moved i.e. return value of fun has new owner

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

