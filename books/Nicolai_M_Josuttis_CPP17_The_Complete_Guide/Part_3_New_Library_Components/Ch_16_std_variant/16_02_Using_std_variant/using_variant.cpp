/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.2 Using std::variant<>

    Initializations and assignment always use the best match to find out the new alternative
    
    empty variants, 
    variants with reference members, 
    variants with C-style array members,
    and variants with incomplete types (such as void) are not allowed

    There is no empty state
    The default constructor initializes the first type with the default constructor

    std::monostate
        To support variants, where the first type has no default constructor
        Objects of type std::monostate always have the same state. 
        Thus, they always compare equal.
        std::monostate can serve as a first alternative type to make the variant type default constructible

    Deriving from Variants
        you can define an aggregate deriving from a std::variant<>

************/

#include <iostream>
#include <string>
#include <variant>

using not_default_cons_t = 
    class NoDefaultConstruct {
        int m_val;
        public:
        NoDefaultConstruct() = delete;
        NoDefaultConstruct(int val) : m_val{val} {}
        int get_val() const { return m_val; }
    };

class DerivedVarinat : public std::variant<std::string, int, double> {

};

int main() {

    try {
        std::cout << "=== using std::variant<> ===\n";
        std::variant<int, double, std::string> vval{"sample string"};
        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';
        std::cout << "std::get<2>(vval): " << std::get<2>(vval) << '\n';
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::holds_alternative<std::string>(vval): " << std::boolalpha << std::holds_alternative<std::string>(vval) << '\n';
        std::cout << '\n';

        vval = 34;
        std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';
        std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::holds_alternative<int>(vval): " << std::boolalpha << std::holds_alternative<int>(vval) << '\n';
        std::cout << '\n';

        vval = 28.67;
        std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';
        std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::holds_alternative<double>(vval): " << std::boolalpha << std::holds_alternative<double>(vval) << '\n';
        std::cout << '\n';
    } catch(const std::bad_variant_access & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    try {
        std::cout << "\n=== std::variant<> invalid access ===\n";
        std::variant<int, double, std::string> vval{"sample string"};

        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';
        std::cout << "std::get<2>(vval): " << std::get<2>(vval) << '\n';
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::holds_alternative<std::string>(vval): " << std::boolalpha << std::holds_alternative<std::string>(vval) << '\n';
        std::cout << '\n';

        [[maybe_unused]] auto val = std::get<int>(vval) << '\n';

    } catch(const std::bad_variant_access & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    {
    std::cout << "\n=== empty std::variant<> ===\n";
    std::variant<std::string, int> empty_vval;

    std::cout << "empty_vval.index(): " << empty_vval.index() << '\n';
    std::cout << "std::get<0>(empty_vval): " << std::get<0>(empty_vval) << '\n';
    }

    {
    std::cout << "\n=== std::variant<> with no default constructor type ===\n";
    //std::variant<not_default_cons_t, int> vval; // CE error: use of deleted function 'std::variant<_Types>::variant() [with _Types = {NoDefaultConstruct, int}]'  
    }

    try{
        std::cout << "\n=== std::monostate std::variant<> ===\n";
        std::variant<std::monostate, not_default_cons_t, int, std::string> vval;
        if(std::holds_alternative<std::monostate>(vval)) {
            std::cout << "std::variant<> has std::monostate\n";
        }
        if(std::get_if<std::monostate>(&vval)) {
            std::cout << "std::variant<> has std::monostate\n";
        }
        std::cout << "vval.index(): " << vval.index() << '\n';
        
        std::cout << "After assignment:\n";
        vval = not_default_cons_t{42};
        if(std::holds_alternative<std::monostate>(vval)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        if(std::get_if<std::monostate>(&vval)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        std::cout << "vval.index(): " << vval.index() << '\n';
        //std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';
        std::cout << '\n';


        std::variant<std::string, std::monostate, not_default_cons_t, int> vval2;
        if(std::holds_alternative<std::monostate>(vval2)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        if(std::get_if<std::monostate>(&vval2)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        std::cout << "vval.index(): " << vval.index() << '\n';

        std::cout << "After assignment:\n";
        vval2 = std::monostate{};
        if(std::holds_alternative<std::monostate>(vval2)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        if(std::get_if<std::monostate>(&vval2)) {
            std::cout << "std::variant<> has std::monostate\n";
        } else {
            std::cout << "std::variant<> does not has std::monostate\n";
        }
        std::cout << "vval2.index(): " << vval2.index() << '\n';
        //std::cout << "std::get<1>(vval2): " << std::get<1>(vval2) << '\n';        
    } catch(std::bad_variant_access & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    try {
    std::cout << "\n=== Deriving from std::variant<> ===\n";

    DerivedVarinat dvobj{4.56};
    std::cout << "std::get<double>(dvobj): " << std::get<double>(dvobj) << '\n';
    std::cout << "std::get<2>(dvobj): " << std::get<2>(dvobj) << '\n';
    std::cout << "dvobj.index(): " << dvobj.index() << '\n';
    std::cout << '\n';

    dvobj.emplace<1>(67);
    std::cout << "std::get<int>(dvobj): " << std::get<int>(dvobj) << '\n';
    std::cout << "std::get<1>(dvobj): " << std::get<1>(dvobj) << '\n';
    std::cout << "dvobj.index(): " << dvobj.index() << '\n';
    std::cout << '\n';

    dvobj.emplace<0>("sample string");
    std::cout << "std::get<std::string>(dvobj): " << std::get<std::string>(dvobj) << '\n';
    std::cout << "std::get<0>(dvobj): " << std::get<0>(dvobj) << '\n';
    std::cout << "dvobj.index(): " << dvobj.index() << '\n';
    std::cout << '\n';      
    } catch(std::bad_variant_access & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }


    {
        std::cout << "\n=== std::variant<> argument to generic lambda ===\n";
        using my_variant_t = std::variant<int, double, std::string>;
        
        auto display = [](const auto & vval){
            if(std::holds_alternative<int>(vval)) {
                std::cout << std::get<int>(vval) << '\n';
            } else if(std::holds_alternative<double>(vval)) {
                std::cout << std::get<double>(vval) << '\n';
            } else if(std::holds_alternative<std::string>(vval)) {
                std::cout << std::get<std::string>(vval) << '\n';
            }
        };

        my_variant_t vval{"sample string"};
        display(vval);

        vval = 53.67;
        display(vval);

        vval = 34;
        display(vval);
    }
    return 0;
}

/*********
    END OF FILE
************/



