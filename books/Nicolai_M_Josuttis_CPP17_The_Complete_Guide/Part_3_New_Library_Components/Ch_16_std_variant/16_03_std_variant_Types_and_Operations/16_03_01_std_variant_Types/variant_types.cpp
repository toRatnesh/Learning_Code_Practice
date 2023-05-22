/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/variant

Chapter 16 std::variant<>
    std::variant<>
        a new union class
        supports a new way of polymorphism and dealing with inhomogeneous collections
        allows us to deal with elements of different data types  without the need for a common base class and pointers (raw or smart).

16.3 std::variant<> Types and Operations

16.3.1 std::variant<> Types

    std::variant<> is a variadic class template
    namespace std {
        template<typename Types...> class variant;
    }

    Additional types
    std::variant_size
    std::variant_alternative
    std::variant_npos
    std::monostate
    std::bad_variant_access -> std::exception

    Additional objects
    std::in_place_type (of type std::in_place_type_t)
    std::in_place_index (of type std::in_place_index_t)

************/

#include <iostream>
#include <string>
#include <variant>
#include <string_view>
#include <utility>
#include <vector>
#include <set>
#include <cassert>
#include <complex>
#include <any>
#include <typeinfo>

class MyType {
    public:
    MyType(int) {}
    MyType(const MyType & ) { 
        throw std::runtime_error(" exception const MyType &");
    }
};



int main() {

    {
        std::cout << "=== std::bad_variant_access ===\n";

        std::variant<std::string, std::string_view, const char *> best_match_variant{"sample string"}; 
        std::cout << "best_match_variant.index(): " << best_match_variant.index() << '\n';
        std::cout << "std::get<const char *>(best_match_variant): " << std::get<const char *>(best_match_variant) << '\n';

        try {
            auto val =   std::get<std::string>(best_match_variant);
        } catch (const std::bad_variant_access & exp) {
            std::cout << "EXCEPTION: " << exp.what() << '\n';
        }
    }

    {
        std::cout << "\n=== std::in_place_type ===\n";

        {
        std::variant<std::complex<double>, int> vval{std::in_place_type<std::complex<double>>, 3.5, 4.8};
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<std::complex<double>>(vval).real(): " << std::get<std::complex<double>>(vval).real() << ", std::get<std::complex<double>>(vval).imag(): " << std::get<std::complex<double>>(vval).imag() << '\n';
        std::cout << "std::get_if<std::complex<double>>(&vval)->real(): " << std::get_if<std::complex<double>>(&vval)->real() << ", std::get_if<std::complex<double>>(&vval)->imag(): " << std::get_if<std::complex<double>>(&vval)->imag() << '\n';
        }      
    }

    {
        std::cout << "\n=== std::in_place_index ===\n";

        auto compFunc = [](int val1, int val2){ return val1 < val2; };
        std::variant<std::vector<int>, std::set<int, decltype(compFunc)>> vval{std::in_place_index<1>, {0, 1, 2, -1, -2}, compFunc};
        std::cout << "set elements: ";
        for(const auto & elem : std::get<1>(vval)) {
            std::cout << elem << ',';
        }
        std::cout << '\n';        
    }

    {
        std::cout << "\n=== std::variant_npos ===\n";

        std::variant<int, double, MyType> vval{49};
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';

        assert(0 == vval.index());
        assert(false == vval.valueless_by_exception());
        assert(49 == std::get<int>(vval));

        try {
            vval = MyType{13};
        } catch (...) {
            if(vval.valueless_by_exception()) {
                std::cout << "std::variant is valueless by exception\n";
                if(std::variant_npos == vval.index()) {
                    std::cout << "vval.index() is std::variant_npos\n";
                }

                assert(std::variant_npos == vval.index());
                assert(true == vval.valueless_by_exception());
            }
        }        
    }

    {
        std::cout << "\n=== std::monostate ===\n";
        std::variant<int, int, double, std::string, std::monostate> vval1{std::in_place_index<0>, 7}, 
            vval21{std::in_place_index<1>, 7}, vval22{std::in_place_index<1>, 7}, vval23{std::in_place_index<1>, 4},
            vval51{std::monostate{}}, vval52{std::monostate{}};

        if(vval1 < vval21) {
            std::cout << "value " << std::get<0>(vval1) << " with alternative index: " << vval1.index() << " is less than with value " << std::get<1>(vval21) << " with alternative index " << vval21.index() << '\n';
        }
        if(vval21 == vval22) {
            std::cout << "value " << std::get<1>(vval21) << " with alternative index: " << vval21.index() << " is equal to value " << std::get<1>(vval22) << " with alternative index " << vval22.index() << '\n';
        }

        if(vval51 == vval52) {
            std::cout << "std::monostate value with alternative index: " << vval51.index() << " is equal to std::monostate value with alternative index " << vval52.index() << '\n';
        }
    }


    {
    std::cout << "\n=== std::variant_size ===\n";        
    static_assert(std::variant_size_v<std::variant<>> == 0);
    static_assert(std::variant_size_v<std::variant<int, float, double>> == 3);
    static_assert(std::variant_size_v<std::variant<std::monostate, void>> == 2);
    static_assert(std::variant_size_v<std::variant<std::variant<std::any>>> == 1);

    std::cout << "std::variant_size_v<std::variant<>>: " << std::variant_size_v<std::variant<>> << '\n';
    std::cout << "std::variant_size_v<std::variant<int, float, double>>: " << std::variant_size_v<std::variant<int, float, double>> << '\n';
    std::cout << "std::variant_size_v<std::variant<std::monostate, void>>: " << std::variant_size_v<std::variant<std::monostate, void>> << '\n';
    std::cout << "std::variant_size_v<std::variant<std::variant<std::any>>>: " << std::variant_size_v<std::variant<std::variant<std::any>>> << '\n';

    }

    {
    std::cout << "\n=== std::variant_alternative ===\n";
    using my_varinat_t = std::variant<int, double, MyType>;
    static_assert(std::is_same_v<int,       std::variant_alternative_t<0, my_varinat_t>>);
    static_assert(std::is_same_v<double,    std::variant_alternative_t<1, my_varinat_t>>);
    static_assert(std::is_same_v<MyType,    std::variant_alternative_t<2, my_varinat_t>>);
    
    std::cout << "typeid(std::variant_alternative_t<0, my_varinat_t>).name(): " << typeid(std::variant_alternative_t<0, my_varinat_t>).name() << '\n';
    std::cout << "typeid(std::variant_alternative_t<1, my_varinat_t>).name(): " << typeid(std::variant_alternative_t<1, my_varinat_t>).name() << '\n';
    std::cout << "typeid(std::variant_alternative_t<2, my_varinat_t>).name(): " << typeid(std::variant_alternative_t<2, my_varinat_t>).name() << '\n';
        
    }

    return 0;
}

/*********
    END OF FILE
************/



