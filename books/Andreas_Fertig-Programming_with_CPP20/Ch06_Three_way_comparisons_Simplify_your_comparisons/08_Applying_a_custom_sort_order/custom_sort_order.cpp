/*****

References
    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
    https://en.cppreference.com/w/cpp/language/default_comparisons

6.8 Applying a custom sort order

    we can either implement the spaceship operator ourselves or default it.
    Sometimes we need a bit of a mixture.

    Consider this example:

**********/

#include <iostream>
#include <cstdint>
#include <string>
#include <compare>

struct Address {
    std::string     m_city;
    std::string     m_street;
    uint32_t        m_street_no;

    auto operator<=>(const Address & ) const = default;
};

struct New_Address {
    std::string     m_city;
    std::string     m_street;
    uint32_t        m_street_no;

    auto operator<=>(const New_Address& rhs) const {
        if(const auto& cmp = m_city <=> rhs.m_city; cmp != 0) {
            return cmp;
        }
        else if(const auto& scmp = m_street <=> rhs.m_street; scmp != 0) {
            return scmp;
        }

        return rhs.m_street_no <=> m_street_no;
    }
    
    bool operator==(const New_Address & ) const = default;
};

template<typename T>
void compareIt(const T & adr1, const T & adr2) {
    const auto res = adr1 <=> adr2;
    if(res == 0) {
        std::puts("same");
    }
    else if(res < 0){
        std::puts("different - less");
    }
    else {
        std::puts("different - greater");
    }
}

int main() {

    Address     adr1{"delhi", "saket", 32};
    New_Address nadr1{"delhi", "saket", 32};
    
    std::puts("=== Two address - same ===");
    {
        Address adr2{"delhi", "saket", 32};
        compareIt(adr1, adr2);
        compareIt(adr2, adr1);        
    }
    {
        New_Address nadr2{"delhi", "saket", 32};
        compareIt(nadr1, nadr2);
        compareIt(nadr2, nadr1);        
    }


    std::puts("=== Two address - city different ===");
    {
        Address adr3{"mumbai", "saket", 32};
        compareIt(adr1, adr3);
        compareIt(adr3, adr1);        
    }
    {
        New_Address nadr3{"mumbai", "saket", 32};
        compareIt(nadr1, nadr3);
        compareIt(nadr3, nadr1);
    }    

    std::puts("=== Two address - street different ===");
    {
        Address adr4{"delhi", "dwarka", 32};
        compareIt(adr1, adr4);
        compareIt(adr4, adr1);        
    }
    {
        New_Address nadr4{"delhi", "dwarka", 32};
        compareIt(nadr1, nadr4);
        compareIt(nadr4, nadr1);         
    }

    std::puts("=== Two address - street number different ===");
    {
        Address adr5{"delhi", "saket", 33};
        compareIt(adr1, adr5);
        compareIt(adr5, adr1);        
    }
    {
        New_Address nadr5{"delhi", "saket", 33};
        compareIt(nadr1, nadr5);
        compareIt(nadr5, nadr1);        
    }

    return 0;
}

/*****
    END OF FILE
**********/


