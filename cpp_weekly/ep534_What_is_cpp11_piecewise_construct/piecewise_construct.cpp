/*****

References:
    episode     https://www.youtube.com/watch?v=XSUlr7yAClc
    https://en.cppreference.com/cpp/utility/piecewise_construct
    https://devblogs.microsoft.com/oldnewthing/20220428-00/?p=106540

    code https://godbolt.org/z/xszrThfY4
    
std::piecewise_construct
    The overloads that do not use std::piecewise_construct_t assume that each tuple argument becomes the element of a pair.
    The overloads that use std::piecewise_construct_t assume that each tuple argument is used to construct, piecewise, a new object of specified type, which will become the element of the pair.

    It may improve performance

**********/

#include <iostream>
#include <string>
#include <map>

class x_key_t {

    std::string     m_name;
    int             m_weight;

    public:
    ~x_key_t() = default;
    x_key_t() = default;

    x_key_t(const std::string name, const int weight) 
        : m_name{name}, m_weight{weight} { 
        
        std::cout << "Constructor: x_key_t(const std::string name, const int weight)\n";

    }

    x_key_t(const x_key_t & other) 
        : m_name{other.m_name}, m_weight{other.m_weight} { 
        
        std::cout << "Copy Constructor: x_key_t(const x_key_t & other)\n";

    }
    
    x_key_t & operator=(const x_key_t & other) 
    { 
        if(this != &other) {
            m_name = other.m_name; 
            m_weight = other.m_weight;
        }
        
        std::cout << "Copy assign: x_key_t(const x_key_t & other)\n";
        return *this;
    }

    x_key_t(x_key_t && other) 
        : m_name{std::move(other.m_name)}, m_weight{std::move(other.m_weight)} { 
        
        std::cout << "Move Constructor: x_key_t(x_key_t && other)\n";

    }

    x_key_t & operator=(x_key_t && other) 
    { 
        if(this != &other) {
            m_name = std::move(other.m_name); 
            m_weight = std::move(other.m_weight);
        }
        
        std::cout << "Move assign: x_key_t(x_key_t && other)\n";

        return *this;
    }

    std::string  name()      const { return m_name; }
    int         weight()    const { return m_weight; }

    bool operator<(const x_key_t & other) const {
        return std::tie(m_name, m_weight) < std::tie(other.m_name, other.m_weight);
    }

    std::string get() const {
        return  m_name + "_" +std::to_string(m_weight);
    }
};

class x_value_t {

    std::string     m_name;
    int             m_value;

    public:
    x_value_t() = default;

    x_value_t(const std::string name, const int value) 
        : m_name{name}, m_value{value} { 
        
    }
    
    std::string  name()      const { return m_name; }
    int         value()    const { return m_value; }

    std::string get() const {
        return m_name +  "_" + std::to_string(m_value);
    }

};

int main()
{

    {

        std::map<std::string, std::string>  lmap;

        lmap.emplace("aaaaa", "1111111");
        lmap.emplace(std::piecewise_construct, std::make_tuple(5, 'b'), std::make_tuple(7, '2'));
        lmap.emplace(std::piecewise_construct, std::forward_as_tuple(5, 'c'), std::forward_as_tuple(7, '3'));

        for(const auto & [k, v] : lmap) {
            std::cout << "key: " << k << ", value: " << v << '\n';
        }

    }
    std::cout << '\n';

    {

        std::map<x_key_t, x_value_t>  lmap;

        x_key_t l_key{"k-1", 1};
        x_value_t l_val{"v-1", 1};

        lmap.emplace(l_key, l_val);
        std::cout << '\n';

        lmap.emplace(x_key_t{"k-2", 2}, x_value_t{"v-2", 2});
        std::cout << '\n';

        // std::piecewise_construct avoids copy or move
        lmap.emplace(std::piecewise_construct, std::make_tuple("k-3", 3), std::make_tuple("v-3", 3));
        std::cout << '\n';

        lmap.emplace(std::piecewise_construct, std::forward_as_tuple("k-4", 4), std::forward_as_tuple("v-4", 4));

        std::cout << '\n';
        for(const auto & [k, v] : lmap) {
            std::cout << "key: " << k.get() << ", value: " << v.get() << '\n';
        }

    }

    return 0;
}

/*****
    END OF FILE
**********/

