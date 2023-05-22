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

16.3.2 std::variant<> Operations

    -----------------------------------------------------
    Operation Effect
    -----------------------------------------------------
    constructors	Create a variant object (might call constructor for underlying type)
    destructor		Destroys an variant object
    =				Assign a new value
    emplace<T>()	Assign a new value to the alternative having type T
    emplace<Idx>()	Assign a new value to the alternative with index Idx
    valueless_by
    _exception()	Returns whether the variant has no value due to an exception
    index()			Returns the index of the current alternative
    swap()			Swaps values between two objects
    ==, !=, <, 
    <=, >, >=		Compare variant objects
    hash<>			Function object type to compute hash values
    holds_
    alternative<T>()Returns whether there is a value for type T
    get<T>()		Returns the value for the alternative with type T or throws
    get<Idx>()		Returns the value for the alternative with index Idx or throws
    get_if<T>()		Returns a pointer to the value for the alternative with type T or nullptr
    get_if<Idx>()	Returns a pointer to the value for the alternative with index Idx or nullptr
    visit()			Perform operation for the current alternative
    -----------------------------------------------------    

    Construction
        the default constructor of a variant calls the default constructor of the first alternative
        the alternative is value initialized, which means that is it 0, false, or nullptr, for fundamental types

        if a value is passed for initialization, the best matching type is used
        the call is ambiguous if two types match equally well

        to pass more than one value for initialization, you have to use the in_place_type or in_place_index
        also use the in_place_index tags to resolve ambiguities or overrule priorities during the initialization

        you can even pass an initializer list followed by additional arguments
        can’t use CTAD for std::variant<> and there is no make_variant<>() convenience function


    Accessing the Value
        call get<>() for the corresponding alternative
        can pass its index
        can pass its type, provided a type is not used more than once
        
        std::get_if<> to access the value with the option to check whether it exists
        must pass a pointer to a variant to get_if<>() and it either returns a pointer to the current value or nullptr
        
        another way are variant visitors
	
    Changing the Value
        assignment and emplace() operations exist corresponding to the initializations
        another way are variant visitors

    Comparisons
        For two variants of the same type (i.e., having the same alternatives in the same order)

        Rules:
        • A variant with a value of an earlier alternative is less than a variant with a value with a later alternative
        • If two variants have the same alternative the corresponding operators for the type of the alternatives are evaluated. 
            All objects of type std::monostate are always equal
        • Two variants with the special state valueless_by_exception() being true are equal. 
            Otherwise, any variant with valueless_by_exception() being true is less than any other variant	

    Move Semantics
        std::variant<> also supports move semantics
        You can also move a value into or out of the contained object.
        If you move the object as a whole, the state gets copied and the value of the current alternative is moved

    Hashing
        The hash value for a variant object is enabled if and only if each member type can provide a hash value. 
        Note that the hash value is not the hash value of the current alternative.

************/

#include <iostream>
#include <string>
#include <variant>
#include <string_view>
#include <complex>
#include <utility>
#include <vector>
#include <set>


int main() {

    {
    std::cout << "=== std::variant<> Construction ===\n";

    std::variant<std::string, int, double> default_variant;
    std::cout << "default_variant.index(): " << default_variant.index() << '\n';
    std::cout << "std::get<std::string>(default_variant): " << std::get<std::string>(default_variant) << '\n';

    //std::variant<int, float> ambiguous_variant{32.5}; // CE error: no matching function for call to 'std::variant<int, float>::variant(<brace-enclosed initializer list>)'
    //std::variant<long, long> ambiguous_variant{32.5};   // CE error: no matching function for call to 'std::variant<long int, long int>::variant(<brace-enclosed initializer list>)'
    //std::variant<std::string, std::string_view> ambiguous_variant{"sample string"}; // CE error: no matching function for call to 'std::variant<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string_view<char, std::char_traits<char> > >::variant(<brace-enclosed initializer list>)'

    {
    std::variant<long, int> best_match_variant{42};
    std::cout << "best_match_variant.index(): " << best_match_variant.index() << '\n';
    std::cout << "std::get<int>(best_match_variant): " << std::get<int>(best_match_variant) << '\n';
    }

    {
    std::variant<std::string, std::string_view, const char *> best_match_variant{"sample string"}; 
    std::cout << "best_match_variant.index(): " << best_match_variant.index() << '\n';
    std::cout << "std::get<const char *>(best_match_variant): " << std::get<const char *>(best_match_variant) << '\n';                   
    }

    {
    //std::variant<std::complex<double>, int> vval{3.5, 4.8}; // CE error: no matching function for call to 'std::variant<std::complex<double>, int>::variant(<brace-enclosed initializer list>)'
    }

    {
    std::variant<std::complex<double>, int> vval{std::in_place_type<std::complex<double>>, 3.5, 4.8};
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<std::complex<double>>(vval).real(): " << std::get<std::complex<double>>(vval).real() << ", std::get<std::complex<double>>(vval).imag(): " << std::get<std::complex<double>>(vval).imag() << '\n';
    std::cout << "std::get_if<std::complex<double>>(&vval)->real(): " << std::get_if<std::complex<double>>(&vval)->real() << ", std::get_if<std::complex<double>>(&vval)->imag(): " << std::get_if<std::complex<double>>(&vval)->imag() << '\n';
    }

    {
    std::variant<std::complex<double>, int> vval{std::in_place_index<0>, 3.5, 4.8};
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<std::complex<double>>(vval).real(): " << std::get<std::complex<double>>(vval).real() << ", std::get<std::complex<double>>(vval).imag(): " << std::get<std::complex<double>>(vval).imag() << '\n';
    std::cout << "std::get_if<std::complex<double>>(&vval)->real(): " << std::get_if<std::complex<double>>(&vval)->real() << ", std::get_if<std::complex<double>>(&vval)->imag(): " << std::get_if<std::complex<double>>(&vval)->imag() << '\n';
    }

    {
    std::variant<int, int> vval{std::in_place_index<1>, 7};
    std::cout << "vval.index(): " << vval.index() << '\n';
    //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';  // CE 
    std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';

    vval.emplace<0>(9);
    std::cout << "vval.index(): " << vval.index() << '\n';
    //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';  // CE 
    std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';    
    }

    {
    auto compFunc = [](int val1, int val2){ return val1 < val2; };
    std::variant<std::vector<int>, std::set<int, decltype(compFunc)>> vval{std::in_place_index<1>, {0, 1, 2, -1, -2}, compFunc};
    std::cout << "set elements: ";
    for(const auto & elem : std::get<1>(vval)) {
        std::cout << elem << ',';
    }
    std::cout << '\n';
    }

    }

    try {
        std::cout << "\n=== Accessing the Value ===\n";
        std::variant<int, int, std::string> vval{std::in_place_index<1>, 9};

        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n'; 

        //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';  // CE: int is used twice
        //std::cout << "std::get<3>(vval): " << std::get<3>(vval) << '\n';      // CE: 3rd index alternative is not present
        //std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';  // CE: double alternative does not exist

        {
            constexpr int index = 1;
            if( const auto ip = std::get_if<index>(&vval); ip) {
                std::cout << "*ip: " << *ip << '\n';
            } else {
                std::cout << "alternative with index " << index << " is not set\n";
            }            
        }

        {
            constexpr int index = 0;
            if( const auto ip = std::get_if<index>(&vval); ip) {
                std::cout << "*ip: " << *ip << '\n';
            } else {
                std::cout << "alternative with index " << index << " is not set\n";
            }            
        }
        auto val = std::get<std::string>(vval);

    } catch(const std::bad_variant_access & exp) {
        std::cout << "EXCEPTION: " << exp.what() << '\n';
    }


    try {
        std::cout << "\n=== Changing the Value ===\n";
        std::variant<int, int, double, std::string> vval;

        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';

        vval = "sample string";
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';

        vval = 56.78;
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';

        //vval = 43;          // CE: because two int are present
        vval.emplace<1>(43);
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';
        //std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';    // CE: because two int are present

        vval.emplace<0>(83);
        std::cout << "vval.index(): " << vval.index() << '\n';
        std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';

        vval = "sample string";
        if(auto lp = std::get_if<std::string>(&vval); lp) {
            *lp = "updated string value";
        } else if(auto lp = std::get_if<double>(&vval); lp) {
            *lp = 12.34;
        } else if(auto lp = std::get_if<1>(&vval); lp) {
            *lp = 20;
        } else if(auto lp = std::get_if<0>(&vval); lp) {
            *lp = 10;
        } 

        std::cout << "vval.index(): " << vval.index() << '\n';
        if(auto lp = std::get_if<std::string>(&vval); lp) {
            std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';
        } else if(auto lp = std::get_if<double>(&vval); lp) {
            std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';
        } else if(auto lp = std::get_if<1>(&vval); lp) {
            std::cout << "std::get<1>(vval): " << std::get<1>(vval) << '\n';
        } else if(auto lp = std::get_if<0>(&vval); lp) {
            std::cout << "std::get<0>(vval): " << std::get<0>(vval) << '\n';
        }

    } catch(const std::bad_variant_access & exp) {
        std::cout << "EXCEPTION: " << exp.what() << '\n';
    }


    try {
        std::cout << "\n=== std::variant<> Comparisons ===\n";
        std::variant<int, int, double, std::string, std::monostate> vval1{std::in_place_index<0>, 7}, 
            vval21{std::in_place_index<1>, 7}, vval22{std::in_place_index<1>, 7}, vval23{std::in_place_index<1>, 4},
            vval51{std::monostate{}}, vval52{std::monostate{}};

        std::variant<int, int, double, std::string, std::monostate> vval3{3.45}, vval4{"sample string"};
        if(vval1 < vval21) {
            std::cout << "value " << std::get<0>(vval1) << " with alternative index: " << vval1.index() << " is less than with value " << std::get<1>(vval21) << " with alternative index " << vval21.index() << '\n';
        }
        if(vval21 == vval22) {
            std::cout << "value " << std::get<1>(vval21) << " with alternative index: " << vval21.index() << " is equal to value " << std::get<1>(vval22) << " with alternative index " << vval22.index() << '\n';
        }
        if(vval21 < vval23) {
            std::cout << "value " << std::get<1>(vval21) << " with alternative index: " << vval21.index() << " is less than with value " << std::get<1>(vval23) << " with alternative index " << vval23.index() << '\n';
        }

        if(vval51 == vval52) {
            std::cout << "std::monostate value with alternative index: " << vval51.index() << " is equal to std::monostate value with alternative index " << vval52.index() << '\n';
        }

        if(vval21 < vval3) {
            std::cout << "value " << std::get<1>(vval21) << " with alternative index: " << vval21.index() << " is less than with value " << std::get<double>(vval3) << " with alternative index " << vval3.index() << '\n';
        }
        
        std::variant<int, std::string> vval{"this can not be comaped with any other variant type"};
        //if(vval4 == vval) std::cout << "this comparison of different types of variant will result in compilation error\n";


    } catch(const std::bad_variant_access & exp) {
        std::cout << "EXCEPTION: " << exp.what() << '\n';
    }

    try {
        std::cout << "\n=== std::variant<> Move Semantics ===\n";
        std::variant<int, double, std::string> vval, vval2{"this will be moved"};
        std::string str = "sample string";
        int     ival = 5;
        double  dval = 6.78;

        vval = std::move(str);
        std::cout << "vval.index(): " << vval.index() << '\n';        
        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';

        vval = std::move(ival);
        std::cout << "vval.index(): " << vval.index() << '\n';        
        std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';

        vval = std::move(dval);
        std::cout << "vval.index(): " << vval.index() << '\n';        
        std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';

        vval = std::move(vval2);
        std::cout << "vval.index(): " << vval.index() << '\n';        
        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';

        std::string strv = std::move(std::get<std::string>(vval));
        std::cout << "moved value from std::variant, strv: " << strv << '\n';
        
        std::cout << "vval.index(): " << vval.index() << '\n';        // state is copied, so accessing its value is OK
        std::cout << "std::get<std::string>(vval): " << std::get<std::string>(vval) << '\n';    // accessing moved value is UB

    } catch(const std::bad_variant_access & exp) {
        std::cout << "EXCEPTION: " << exp.what() << '\n';
    }

    try { 
        std::cout << "\n=== std::variant<> Hashing ===\n";

        std::string str = "sample string";
        std::cout << "std::hash<std::string>{}(str):      " << std::hash<std::string>{}(str) << '\n';

        using my_variant_t = std::variant<int, double, std::string>;
        my_variant_t vval1{str};
        std::cout << "std::hash<my_variant_t>{}(vval1):   " << std::hash<my_variant_t>{}(vval1) << '\n';
        
        using your_variant_t = std::variant<int, std::string>;
        your_variant_t vval2{str};
        std::cout << "std::hash<your_variant_t>{}(vval2): " << std::hash<your_variant_t>{}(vval2) << '\n';
                

    } catch(const std::bad_variant_access & exp) {
        std::cout << "EXCEPTION: " << exp.what() << '\n';
    }

    return 0;
}

/*********
    END OF FILE
************/




