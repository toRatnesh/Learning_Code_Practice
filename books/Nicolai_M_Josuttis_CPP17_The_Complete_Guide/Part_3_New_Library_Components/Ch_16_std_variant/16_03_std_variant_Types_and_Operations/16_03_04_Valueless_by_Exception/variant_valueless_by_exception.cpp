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

16.3.4 Valueless by Exception

    if std::variant<> modification throws an exception, then
    var.valueless_by_exception() returns true
    var.index() returns std::variant_npos
    which signals that the variant holds no value at all

    guarantees:
    If emplace() throws valueless_by_exception() is always set to true

    If operator=() throws and the modification would not change the alternative valueless_by_exception() and index() keeps their old state. 
    The state of the value depends on the exception guarantees of the value type.

    If operator=() throws and the new value would set a different alternative, the variant might hold no value (valueless_by_exception() might become true). 
    This depends on when exactly the exception gets thrown. 
    If it happens during a type conversion before the actual modification of the value started, the variant will still hold its old value.

    If you still want to use a variant although using it caused an exception, you should better check its state.

************/

#include <iostream>
#include <string>
#include <variant>
#include <exception>
#include <cassert>

class MyType {
    public:
    MyType(int) {}
    MyType(const MyType & ) { 
        throw std::runtime_error(" exception const MyType &");
    }
};

int main() {

    std::cout << "=== variant initially ===\n";

    std::variant<int, double, MyType> vval{49};
    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';

    assert(0 == vval.index());
    assert(false == vval.valueless_by_exception());
    assert(49 == std::get<int>(vval));

    std::cout << "\n=== Valueless by Exception ===\n";
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

        } else {
            std::cout << "vval.index(): " << vval.index() << '\n';
            std::cout << "std::get<int>(vval): " << std::get<int>(vval) << '\n';
        }
    }

    std::cout << "\n=== after assginment to variant object ===\n";
    vval = 56.78;
    assert(1 == vval.index());
    assert(false == vval.valueless_by_exception());
    assert(56.78 == std::get<double>(vval));

    std::cout << "vval.index(): " << vval.index() << '\n';
    std::cout << "std::get<double>(vval): " << std::get<double>(vval) << '\n';

    return 0;
}

/*********
    END OF FILE
************/


