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
	
17.1 Using std::any

    std::any may be declared empty or to be initialized by a value of a specific type
    if the object is empty, the type ID is typeid(void)

    std::any_cast<> creates an object of the passed type
    it creates a temporary object (a prvalue), which is then used to initialize the new object s
    without such an initialization, it is usually better to cast to a reference type to avoid creating a temporary object
    
    std::any_cast for the address of a std::any object, returns a corresponding pointer if the type fits or nullptr if not

    has_value() check, whether the object is empty
    values are stored using their decayed type (arrays convert to pointers, and top-level references and const are ignored)

    because the type is only known at run time, 
    no generic lambdas can be used to deal with the current value independent from its type

    it is possible, to put std::any objects in a container

************/

#include <iostream>
#include <any>
#include <typeinfo>
#include <cassert>
#include <string>
#include <vector>

int main() {

    std::cout << "=== std::any construction ===\n";
    std::any any_default;
    std::any any_ival{5};
    
    assert(any_default.type() == typeid(void));
    assert(any_ival.type() == typeid(int));
    
    std::cout << "any_ival.type().name(): " << any_ival.type().name() << ", std::any_cast<int>(any_ival): " << std::any_cast<int>(any_ival) << '\n';

    std::cout << "\n === std::any_cast<> ===\n";
    try {
        [[maybe_unused]] auto val = std::any_cast<int>(any_default);
    }
    catch(const std::bad_any_cast & exp) {
        std::cout << "Exception while casting empty std::any object: " << exp.what() << '\n';
    }

    try {
        [[maybe_unused]] auto val = std::any_cast<double>(any_ival);
    }
    catch(const std::bad_any_cast & exp) {
        std::cout << "Exception while casting std::any object to different type: " << exp.what() << '\n';
    }

    std::cout << "\n === std::any_cast<> to reference type ===\n";

    std::any any_sval{std::string("sample string")};
    assert(any_sval.type() == typeid(std::string));
    try {
        // cast by value creates a temporary object to initialize
        std::string sval = std::any_cast<std::string>(any_sval);
        std::cout << "sval: " << sval << ", std::any_cast<std::string>(any_sval): " << std::any_cast<std::string>(any_sval) << '\n';
        sval = "changed string value";
        std::cout << "sval: " << sval << ", std::any_cast<std::string>(any_sval): " << std::any_cast<std::string>(any_sval) << '\n';
        std::cout << '\n';
        
        // cast by reference avoids creating temporary object
        const std::string & csrval = std::any_cast<const std::string &>(any_sval);
        std::cout << "csrval: " << csrval << ", std::any_cast<const std::string &>(any_sval): " << std::any_cast<const std::string &>(any_sval) << '\n';
        std::cout << '\n';
        
        std::string & srval = std::any_cast<std::string &>(any_sval);
        std::cout << "srval: " << srval << ", std::any_cast<std::string &>(any_sval): " << std::any_cast<std::string &>(any_sval) << '\n';
        srval = "changed string value - 01";
        std::cout << "srval: " << srval << ", std::any_cast<std::string &>(any_sval): " << std::any_cast<std::string &>(any_sval) << '\n';
        std::any_cast<std::string &>(any_sval) = "changed string value - 02";
        std::cout << "srval: " << srval << ", std::any_cast<std::string &>(any_sval): " << std::any_cast<std::string &>(any_sval) << '\n';
    }
    catch(const std::bad_any_cast & exp) {
        std::cout << "Exception: " << exp.what() << '\n';
    }

    std::cout << "\n === std::any_cast<> to pointer type ===\n";

    auto ptr_val = std::any_cast<std::string>(&any_sval);
    std::cout << "" << typeid(ptr_val).name() << '\n';

    if(ptr_val) {
        std::cout << "*ptr_val: " << *ptr_val << ", *(std::any_cast<std::string>(&any_sval)): " << *(std::any_cast<std::string>(&any_sval)) << '\n';
    }
    *ptr_val = "sample string";
    std::cout << "*ptr_val: " << *ptr_val << ", *(std::any_cast<std::string>(&any_sval)): " << *(std::any_cast<std::string>(&any_sval)) << '\n';

    std::cout << "\n === reset std::any to empty ===\n";

    {
        std::any any_dval{5.5};
        any_dval.reset();
        if(false == any_dval.has_value()) { std::cout << "std:any is empty\n"; }
    }
    {
        std::any any_dval{5.5};
        any_dval = {};
        if(false == any_dval.has_value()) { std::cout << "std:any is empty\n"; }
    }    
    {
        std::any any_dval{5.5};
        any_dval = std::any{};
        if(false == any_dval.has_value()) { std::cout << "std:any is empty\n"; }
    }
    
    std::cout << "\n === container of std::any object === \n";
    std::vector<std::any> vec;
    vec.push_back(42);
    vec.push_back(30.89);
    vec.push_back("char array");
    vec.push_back(std::string("sample string"));

    std::cout << "container elements: \n";
    for(const auto & elem : vec) {
        if(typeid(int) == elem.type()) {
            std::cout << "int : " << std::any_cast<int>(elem) << '\n'; 
        }
        else if(typeid(double) == elem.type()) {
            std::cout << "doule : " << std::any_cast<double>(elem) << '\n'; 
        }
        else if(typeid(std::string) == elem.type()) {
            std::cout << "std::string : " << std::any_cast<const std::string &>(elem) << '\n'; 
        }
        else if(typeid(const char *) == elem.type()) {
            std::cout << "const char * : " << std::any_cast<const char *>(elem) << '\n'; 
        }        
    }

    std::cout << "\n === std::any passed to generic lamda === \n";
    auto lambda = [](auto val) {
        if (typeid(val) == typeid(std::any)) {
            std::cout << "Inside lambda std::any_cast<int>(val): " << std::any_cast<int>(val) << '\n';
        }
        
    };
    lambda(any_ival);

    return 0;
}

/*********
    END OF FILE
************/



