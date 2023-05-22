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

15.3 Special Cases

15.3.1 Optional of Boolean or Raw Pointer Values
    using the comparison operator has different semantics than using an optional object as a Boolean value
    This can become confusing if the contained type is bool or a pointer type

15.3.2 Optional of Optional
    you can also define an optional of an optional value
    a std::variant<> with two Boolean or monostate alternatives might be more appropriate  

************/

#include <iostream>
#include <optional>

int main() {

    // using the comparison operator has different semantics than using an optional object as a Boolean value
    std::cout << "=== Optional of Boolean ===\n";
    {
        std::optional<bool> op_bool{false};
        if(op_bool) {   // true because optional object contains value
            std::cout << "std::optional<bool> object contains value: " 
            << std::boolalpha << *op_bool 
            << "\nalthough optional object contains false value its evaluation as boolean expression results in true because it contains a value";
        }
        if(op_bool == false) {
            std::cout << "comparison of std::optional<bool> with a boolean vlaue, compares with the contained value\n";
            std::cout << "comparison of std::optional<bool> with contained value: " << std::boolalpha << *op_bool 
            << " and boolean value: " << false << " results in true\n"; 
        }

        std::optional<int *> op_intp{nullptr};
        if(op_intp) {
            std::cout << "although std::optional<int *> object contains nullptr, its evaluation as boolean results in true\n"; 
        }

        if(op_intp == nullptr) {
            std::cout << "comparison of std::optional<int *> object which contains nullptr value, and nullptr results in true\n"; 
        }
    }

    std::cout << "\n=== Optional of Optional ===\n";
    {
        std::optional<std::optional<std::string>> op_op_sval{"sample string"};
        if(!op_op_sval) std::cout << "No value\n";
        if(op_op_sval && !*op_op_sval) std::cout << "No inner value\n";
        if(op_op_sval && *op_op_sval) std::cout << "optional of optional value, **op_op_sval: " << **op_op_sval << '\n';
    }
    {
        std::optional<std::optional<std::string>> op_op_sval;
        if(!op_op_sval) std::cout << "No value\n";
        if(op_op_sval && !*op_op_sval) std::cout << "No inner value\n";
        if(op_op_sval && *op_op_sval) std::cout << "optional of optional value, **op_op_sval: " << **op_op_sval << '\n';
    }
    {
        std::optional<std::optional<std::string>> op_op_sval{std::in_place, std::in_place, "sample string"};
        if(!op_op_sval) std::cout << "No value\n";
        if(op_op_sval && !*op_op_sval) std::cout << "No inner value\n";
        if(op_op_sval && *op_op_sval) std::cout << "optional of optional value, **op_op_sval: " << **op_op_sval << '\n';

        *op_op_sval = std::nullopt;
        if(!op_op_sval) std::cout << "No value\n";
        if(op_op_sval && !*op_op_sval) std::cout << "No inner value\n";
        if(op_op_sval && *op_op_sval) std::cout << "optional of optional value, **op_op_sval: " << **op_op_sval << '\n';        
    }

    return 0;
}

/*********
    END OF FILE
************/



