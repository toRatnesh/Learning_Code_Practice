/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/any

Chapter 17 std::any

	std::any can hold values of any arbitrary type but they know which type the value has they currently hold
	objects contain both the contained value and the type of the contained value using typeid
	
	because the value can have any size the memory might be allocated on the heap
	run-time checks can be done to find out, which type the current value has and to use that value as its type a any_cast<> is necessary
	
	as for std::optional<> and std::variant<> the resulting objects have value semantics that is, copying happens deeply
	because heap memory might be involved, copying a std::any usually is expensive and you should prefer to pass objects by reference or move values
	
17.2 std::any Types and Operations

17.2.1 Any Types

    namespace std {
        class any;
    }
    std::any is no class template at all
    std::bad_any_cast -> std::bad_cast -> std::exception // inheritance
    any objects also use the objects std::in_place_type

    values are stored using their decayed type 
    (arrays convert to pointers, and top-level references and const are ignored).
    Even the type passed to in_place_type decays

17.2.2 Any Operations

    ---------------------------------------------------------------
    Operation       Effect
    ---------------------------------------------------------------
    constructors    Create a any object (might call constructor for underlying type)
    make_any()      Create a any object (passing value(s) to initialize it)
    destructor      Destroys an any object
    =               Assign a new value
    emplace<T>()    Assign a new value having the type T
    reset()         Destroys any value (makes the object empty)
    has_value()     Returns whether the object has a value
    type()          Returns the current type as std::type_info object
    any_cast<T>()   Use current value as value of type T (exception if other type)
    swap()          Swaps values between two objects
    ---------------------------------------------------------------

Construction
    To hold a different type than the type of the initial value, you have to use the in_place_type tags
    To initialize an optional object by multiple arguments, you have to create the object or add std::in_place_type as first argument
    make_any<>() can be used for single or multiple arguments (without the need for the in_place_type argument)

Changing the Value
    assignment and emplace() operations exist

Accessing the Value
    cast it to its type with a std::any_cast<>
    The type fits if the passed type with top-level references removed has the same type ID
    
    You can pass an address to get the nullptr if the cast fails, because the current type doesn’t fit
    Note that here casting to a reference results in a run-time error

Move Semantics
    move semantics is only supported for type that also have copy semantics
    move-only types are not supported as contained value types

************/

#include <iostream>
#include <any>
#include <typeinfo>
#include <cassert>
#include <string>
#include <complex>
#include <utility>
#include <set>

int main() {

    std::cout << "=== std::any construction ===\n";
    std::any any_default;
    std::any any_ival{5};
    std::any any_cpval = "const char pointer";

    std::cout << "\n === hold different type than initial value === \n";
    // To hold a different type than the type of the initial value, you have to use the in_place_type tags
    std::any ival{std::in_place_type<unsigned int>, 42.89};
    std::any sval{std::in_place_type<std::string>, "const char pointer as string"};
    std::any cval{std::in_place_type<const char[16]>, "char array"};

    assert(ival.type() == typeid(unsigned int));
    assert(sval.type() == typeid(std::string));
    assert(cval.type() == typeid(const char *));
    //assert(cval.type() == typeid(const char [16])); // fails because type decay to const char *
    assert(cval.type() == typeid(const char *));

    std::cout << "std::any_cast<unsigned int>(ival): " << std::any_cast<unsigned int>(ival) << '\n';
    std::cout << "std::any_cast<std::string>(sval): " << std::any_cast<std::string>(sval) << '\n';

    std::cout << "\n === initialize an any object by multiple arguments === \n";
    // To initialize an any object by multiple arguments, you have to create the object or add std::in_place_type as first argument
    {
        std::any comval{std::complex{4, 6}};
        std::cout << "std::any_cast<std::complex<int>>(comval).real(): " << std::any_cast<std::complex<int>>(comval).real() << ", std::any_cast<std::complex<int>>(comval).imag() " << std::any_cast<std::complex<int>>(comval).imag() << '\n';
    }
    {
        std::any comval{std::in_place_type<std::complex<int>>, 9, 7};
        std::cout << "std::any_cast<std::complex<int>>(comval).real(): " << std::any_cast<std::complex<int>>(comval).real() << ", std::any_cast<std::complex<int>>(comval).imag() " << std::any_cast<std::complex<int>>(comval).imag() << '\n';
    }
    auto compFun = [](int x, int y){ return x < y; };
    {
        std::any any_set{std::in_place_type<std::set<int, decltype(compFun)>>, {-2, -1, 0, 1, 2}, compFun};
        auto setval = std::any_cast<std::set<int, decltype(compFun)>>(any_set);
        std::cout << "set elements: ";
        for(const auto & elem : setval) {
            std::cout << elem << ", ";
        }
        std::cout << '\n';
    }    

    std::cout << "\n === make_any<>() === \n";
    // make_any<>() can be used for single or multiple arguments (without the need for the in_place_type argument)
    {
        auto ival = std::make_any<int>(42);
        auto uval = std::make_any<unsigned int>(83.85);
        auto comval = std::make_any<std::complex<int>>(11, 13);
        auto setval = std::make_any<std::set<int, decltype(compFun)>>({-2, -1, 0, 1, 2}, compFun);

        std::cout << "std::any_cast<int>(ival): " << std::any_cast<int>(ival) << '\n';
        std::cout << "std::any_cast<unsigned int>(uval): " << std::any_cast<unsigned int>(uval) << '\n';
        std::cout << "std::any_cast<std::complex<int>>(comval).real(): " << std::any_cast<std::complex<int>>(comval).real() << ", std::any_cast<std::complex<int>>(comval).imag() " << std::any_cast<std::complex<int>>(comval).imag() << '\n';
        auto sval = std::any_cast<std::set<int, decltype(compFun)>>(setval);
        std::cout << "set elements: ";
        for(const auto & elem : sval) {
            std::cout << elem << ", ";
        }
        std::cout << '\n';
    }

    std::cout << "\n === assignment and emplace() === \n";
    {
        std::any any_obj;
        assert(any_obj.type() == typeid(void));

        any_obj = 45;
        assert(any_obj.type() == typeid(int));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<int>(any_obj): " << std::any_cast<int>(any_obj) << '\n';

        any_obj.emplace<int>(45);
        assert(any_obj.type() == typeid(int));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<int>(any_obj): " << std::any_cast<int>(any_obj) << '\n';


        any_obj = "sample char pointer";
        assert(any_obj.type() == typeid(const char *));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<const char *>(any_obj): " << std::any_cast<const char *>(any_obj) << '\n';

        any_obj.emplace<const char *>("sample char pointer");
        assert(any_obj.type() == typeid(const char *));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<const char *>(any_obj): " << std::any_cast<const char *>(any_obj) << '\n';


        any_obj = std::string("sample string");
        assert(any_obj.type() == typeid(std::string));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<std::string>(any_obj): " << std::any_cast<std::string>(any_obj) << '\n';

        any_obj.emplace<std::string>("sample string");
        assert(any_obj.type() == typeid(std::string));
        std::cout << "any_obj.type().name(): " << any_obj.type().name() << ", std::any_cast<std::string>(any_obj): " << std::any_cast<std::string>(any_obj) << '\n';

    }

    std::cout << "\n === std::any_cast<> === \n";
    {
        std::any sval{std::string("sample string")};
        std::cout << "copy vlaue using prvalue, std::any_cast<std::string>(sval): " << std::any_cast<std::string>(sval) << '\n';
        

        //std::any_cast<const std::string &>(sval) = std::string("this will fail because trying to modify const reference");
        std::cout << "read only ref, this avoids copying and doesn't allow modification, std::any_cast<const std::string &>(sval): " << std::any_cast<const std::string &>(sval) << '\n';
        
        std::cout << "read-write ref, this avoids copying and allow modification, std::any_cast<std::string &>(sval): " << std::any_cast<std::string &>(sval) << '\n';
        std::any_cast<std::string &>(sval) = "updated sample string";
        std::cout << "read-write ref, this avoids copying and allow modification, std::any_cast<std::string &>(sval): " << std::any_cast<std::string &>(sval) << '\n';

        // cast pointer
        //std::any_cast<const std::string>(&sval) = "this will fail";
        std::cout << "read using pointer, *(std::any_cast<const std::string>(&sval)): " << *(std::any_cast<const std::string>(&sval)) << '\n';
        std::cout << "read-write using pointer, *(std::any_cast<std::string>(&sval)): " << *(std::any_cast<std::string>(&sval)) << '\n';
        *(std::any_cast<std::string>(&sval)) = "new sample string";
        std::cout << "read-write using pointer, *(std::any_cast<std::string>(&sval)): " << *(std::any_cast<std::string>(&sval)) << '\n';
        
        //(std::any_cast<std::string &>(&sval)) = "new sample string"; // error: static assertion failed: Template argument must be constructible from an rvalue

    }

    std::cout << "\n === move semantics ===\n";
    {
        std::string str{"sample string"};
        
        std::any sval;
        sval = std::move(str);
        std::cout << "std::any_cast<const std::string &>(sval): " << std::any_cast<const std::string &>(sval) << '\n';

        auto str2 = std::move(std::any_cast<std::string &>(sval));
        std::cout << "str2: " << str2 << '\n';
        /*
        As usual for moved-from objects the contained value of a is unspecified after the last call. 
        Thus, you can use a as a string as long as you don’t make any assumption about which value the contained string value has. 
        The output of the following statement will then probably be the empty string, not "NIL"
        */

        if(sval.has_value()) {
            std::cout << "std::any_cast<const std::string &>(sval): " << std::any_cast<const std::string &>(sval) << '\n';
        }
        else {
            std::cout << "std::any does not have any value\n";
        }

        sval = std::string("needs additional move");
        str2 = std::any_cast<std::string>(std::move(sval)); // needs additional move
        std::cout << "str2: " << str2 << '\n';

        sval = std::string("error casting to rvalue");
        //str2 = std::any_cast<std::string &&>(sval); // error: static assertion failed: Template argument must be constructible from an lvalue

        std::string str3{"move it"};
        std::any empty_val;
        //std::any_cast<std::string &>(empty_val) = std::move(str3);  // fails because empty_val does not hold a string
        empty_val = std::move(str3);
        std::cout << "std::any_cast<const std::string &>(empty_val): " << std::any_cast<const std::string &>(empty_val) << '\n';
        
        str3 = "will work now as empty_val holds a string";
        // This only works if std::any object already contains a value of type std::string
        std::any_cast<std::string &>(empty_val) = std::move(str3);
        std::cout << "std::any_cast<const std::string &>(empty_val): " << std::any_cast<const std::string &>(empty_val) << '\n';
    }

    return 0;
}

/*********
    END OF FILE
************/


