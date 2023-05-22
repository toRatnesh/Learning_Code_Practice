/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.1 Motivation of std::variant<>
    C++ unions are objects able to hold one of a list of possible types
    Drawbacks of C++ unions
        objects do not know, which type of value they currently hold
        can’t derive from a union
        can’t have non-trivial members, such as std::string (without specific effort)

    std::variant<>, a closed discriminated union
        the type of the current value is always known
        that can have members of any specified type, and
        you can derive from

    Variants have internal memory for the maximum size of the underlying types plus some fixed overhead to manage which alternative is used.
    No heap memory is allocated.

    variants can’t be empty unless you use a specific alternative to signal emptiness
    in very rare cases (such as due to exceptions during the assignment of a new value of a different 
    type) the variant can come into a state having no value at all

    std::optional<> and std::any the resulting objects have value semantics
    Copying happens deeply

    Move semantics is supported.

************/

#include <iostream>
#include <string>
#include <variant>

int main() {
    std::cout << "=== C++ union ===\n";
    {
    union U {
        int         ival;
        double      dval;
    };

    U u1{2};
    std::cout << "u1.ival: " << u1.ival << '\n';
    std::cout << "u1.dval: " << u1.dval << '\n';        
    }

    {
    union U {
        int         ival;
        double      dval;
        std::string sval;   // non-trivial member
    };
    //U u1{2};    // error: use of deleted function 'main()::U::~U()'      
    }

    std::cout << "=== C++ std::variant<> ===\n";
    {
    std::variant<int, double, std::string> vval{"sample string"};
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';
    std::cout << "std::holds_alternative<std::string>(vval): " << std::boolalpha << std::holds_alternative<std::string>(vval) << '\n';

    vval = 34;
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';
    std::cout << "std::holds_alternative<int>(vval): " << std::boolalpha << std::holds_alternative<int>(vval) << '\n';

    vval = 28.67;
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';
    std::cout << "std::holds_alternative<double>(vval): " << std::boolalpha << std::holds_alternative<double>(vval) << '\n';
    }


    {
        union U {
            int     ival1;
            int     ival2;
            double  dval;
        };
        U u;
        u.ival1 = 3;
        std::cout << "u.ival1: " << u.ival1 << '\n';
        u.ival2 = 4;
        std::cout << "u.ival2: " << u.ival2 << '\n';
        u.dval  = 4.6;
        std::cout << "u.dval: " << u.dval << '\n';  
        
        std::variant<int, int, double> vval;

        vval.emplace<0>(5);
        std::cout << "vval.index(): " << vval.index() << '\n';
        //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n'; // Compilation error
        std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';

        vval.emplace<1>(7);
        std::cout << "vval.index(): " << vval.index() << '\n';
        //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n'; // Compilation error
        std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';


    }
    return 0;
}

/*********
    END OF FILE
************/


