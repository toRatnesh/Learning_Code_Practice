/*********

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/utility/optional

Chapter 15 std::optional<>

    we could have a value of a certain type or we might not have any value at all
    to define an object of a certain type with an additional Boolean member/flag signaling whether a value exists
    std::optional<> provides such objects in a type-safe way

    size usually is one byte larger than the contained object

    as with std::variant<> and std::any the resulting objects have value semantics
    that is, copying is implemented as a deep copy
    Move semantics are supported.

15.1 Using std::optional<>

15.1 Using std::optional<>
    std::optional<> model a nullable instance of an arbitrary type
    you could also argue that a std::optional<> is a container for zero or one element

15.1.1 Optional Return Values
    we either return the object (e.g. int), which initializes the return value with an object (e.g int),
    or we return std::nullopt, signaling that we don’t have an object value (e.g. int)

    For std::optional<int> oi we evaluate, whether we have a value (by evaluating the object as Boolean expression) 
    and access the value by “dereferencing” the optional object
    if (oi) { 
        std::cout << "convert '" << s << "' to int: " << *oi << "\n"; 
    }

    alternative ways
    if (oi.has_value()) {
        std::cout << "convert '" << s << "' to int: " << oi.value() << "\n";
    }

    has_value() used to check, whether a value was returned
    value()     to access value, value() is safer than operator *: It throws an exception if no value exists

    Operator * should only be used when you are sure that the optional contains a value; 
    otherwise your program will have undefined behavior

15.1.2 Optional Arguments and Data Members

    as usual for types with value semantics, 
    the best way to define a constructor initializing the corresponding members 
    is to take the arguments by value and move the parameters to the member

    value_or(), which enables to specify a fallback value in case no value exists

************/

#include <iostream>
#include <optional>
#include <string>
#include <iomanip>

std::optional<int> asInt_01(const std::string & str) {
    try {
        return std::stoi(str);
    }
    catch(...) {
        return std::nullopt;
    }
}

std::optional<int> asInt_02(const std::string & str) {
    std::optional<int> result;
    try {
        result = std::stoi(str);
    }
    catch(...) {
        result = std::nullopt; 
        /*
            Following can also be used
            nothing 
            result = {};
        */
    }
    return result;
}

auto fun = [](auto op_val)  {
    if(op_val) {
        std::cout << "optional value is: " << *op_val << '\n';
    }
    return 0;
};

class S {
    std::optional<std::string> m_op_str;
    public:
    S(std::string val) : m_op_str(std::move(val)) {}
    void display() {
        std::cout << "optional member is: " << m_op_str.value_or("") << '\n';
    }
};

int main() {

    std::cout << "=== std::optional declaration ===\n";
    std::optional<std::string>  empty_op_string;
    std::optional<std::string>  op_string{"sample string"};   
    std::cout << "accessing empty optional is undefined behavior, *empty_op_string: " << *empty_op_string << '\n';
    std::cout << "accessing optional, *op_string: " << *op_string << '\n';

    std::cout << "\n=== std::optional as return value ===\n";
    for(auto strval : {"13", "0765", "0xF9A", "34ignorealpha", "exception13"} ) {
        std::optional<int> ret = asInt_01(strval);
        if(ret) {
            std::cout << "string strval: " << std::quoted(strval) << ", converted to int value is, *ret: " << *ret << '\n';
        }
        else {
            std::cout << "could not convert string " << std::quoted(strval) << " to int" << '\n';
        }
    }
    std::cout << '\n';

    for(auto strval : {"13", "0765", "0xF9A", "34ignorealpha", "exception13"} ) {
        std::optional<int> ret = asInt_02(strval);
        if(ret.has_value()) {
            std::cout << "string strval: " << std::quoted(strval) << ", converted to int value is, ret.value(): " << ret.value() << '\n';
        }
        else {
            std::cout << "could not convert string " << std::quoted(strval) << " to int" << '\n';
        }
    }

    std::cout << "\n=== std::optional as argument and data member ===\n";
    {
        std::optional<int> op_ival{56};
        fun(op_ival);

        S s{"sample string member"};
        s.display();
    }
    return 0;
}

/*********
    END OF FILE
************/


