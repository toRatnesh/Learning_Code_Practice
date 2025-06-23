/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

6.7 The power of the default spaceship

	We got rid of the ridiculous boiler-plate code.
	Our code is now safer, and correct by default.
	Adding an extra member does not require touching the comparison operators at all.

**********/

#include <iostream>
#include <cstdint>
#include <string>
#include <compare>

struct Person {
    std::string m_name;
    uint8_t m_age;

    bool operator==(const Person & other) const {
        return (m_name == other.m_name) && (m_age == other.m_age);
    }
    bool operator!=(const Person & other) const {
        return not(*this == other);
    }    
};

struct PersonPreCpp20 {
    uint64_t    m_id;
    std::string m_name;
    uint8_t m_age;

    bool operator==(const PersonPreCpp20 & other) const {
        return (m_id == other.m_id) && (m_name == other.m_name) && (m_age == other.m_age);
    }
    bool operator!=(const PersonPreCpp20 & other) const {
        return not(*this == other);
    }    
};

struct PersonCpp20 {
    uint64_t    m_id;
    std::string m_name;
    uint8_t m_age;

    auto operator<=>(const PersonCpp20 & other) const = default;   
};

template<typename T>
void checkEqual(const T & t1, const T & t2) {
    const auto res = t1 == t2;
    if(res) {
        std::puts("same");
    }
    else {
        std::puts("different");
    }
}

int main() {
    {
        Person p1{"Person-1", 32};
        Person p2{"Person-1", 32};
        Person p3{"Person-1", 31};

        checkEqual(p1, p2);
        checkEqual(p1, p3);
    }

    {
        PersonPreCpp20 p1{123, "Person-1", 32};
        PersonPreCpp20 p2{123, "Person-1", 32};
        PersonPreCpp20 p3{345, "Person-1", 31};

        checkEqual(p1, p2);
        checkEqual(p1, p3);
    }
    
    {
        PersonCpp20 p1{123, "Person-1", 32};
        PersonCpp20 p2{123, "Person-1", 32};
        PersonCpp20 p3{345, "Person-1", 31};

        checkEqual(p1, p2);
        checkEqual(p1, p3);
    }

    return 0;
}

/*****
    END OF FILE
**********/


