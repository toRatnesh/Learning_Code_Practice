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

16.3.3 Visitors

unambiguously provide a function call operator for each possible type
corresponding overload is used to deal with the current alternative

    Using Function Objects as Visitors
        call of visit() is a compile-time error if not all possible types are supported by an operator() or the call is ambiguous
        can also use visitors to modify the value of the current alternative (but not to assign a new alternative)
        only the type matters, you can’t have different behavior for alternatives that have the same type
        function call operators should be marked as being const, because they are stateless (they don’t change their behavior, only the passed value)
        
    Using Generic Lambdas as Visitors
        can even still handle the different alternatives differently using the compile-time if language feature

    Using Overloaded Lambdas as Visitors
        using an overloader for function objects and lambdas
        can also define a set of lambdas where the best match is used as visitor

************/

#include <iostream>
#include <string>
#include <variant>

template<typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};
// CTAD rule
template<typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

int main() {

    {
    std::cout << "=== Using Function Objects as Visitors ===\n";
    
    struct MyVisitor {
        void operator()(int val) const {
            std::cout << "int " << val << '\n';
        }
        void operator()(double val) const {
            std::cout << "double " << val << '\n';
        }
        void operator()(std::string val) const {
            std::cout << "std::string " << val << '\n';
        }                
    };
    
    struct TwiceVariantValue {
        void operator()(int & val) const {      // const stateless member function
            val = val * 2;
        }
        void operator()(double & val) const {
            val = val * 2.0;
        }
        void operator()(std::string & val) const {
            val = val + " " + val;
        }                
    };

    std::variant<int, double, std::string> vval{54};
    
    std::visit(MyVisitor{}, vval);
    std::visit(TwiceVariantValue{}, vval);
    std::visit(MyVisitor{}, vval);

    vval = 12.34;
    std::visit(MyVisitor{}, vval);
    std::visit(TwiceVariantValue{}, vval);
    std::visit(MyVisitor{}, vval);

    vval = "sample string";
    std::visit(MyVisitor{}, vval);
    std::visit(TwiceVariantValue{}, vval);
    std::visit(MyVisitor{}, vval);
    }

    {    
    std::cout << "\n=== Using Generic Lambdas as Visitors ===\n";
    std::variant<int, double, std::string> vval{54};
    auto displayVariant = [](const auto & val){ std::cout << val << '\n';};
    
    {
    auto twiceVariant   = [](auto & val) { val = val + val; };

    std::visit([](const auto & val){ std::cout << val << '\n';}, vval); // in-place lambda can also be used
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);

    vval = 34.56;
    std::visit([](const auto & val){ std::cout << val << '\n';}, vval); // in-place lambda can also be used
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);

    vval = "Generic lambda as visitor";
    std::visit([](const auto & val){ std::cout << val << '\n';}, vval); // in-place lambda can also be used
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);
    }

    {
    auto twiceVariant   = [](auto & val) { 
        if constexpr(std::is_convertible_v<decltype(val), std::string>) {
            val = val + " " + val;
        } else {
            val = val * 2;;
        }
    };

    vval = "Generic lambda with constexpr-if";
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);

    vval = 63;
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);

    vval = 81.23;
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);
    }
    }

    {
    std::cout << "\n=== Using Overloaded Lambdas as Visitors ===\n";    
    auto displayVariant = Overload{
        [](int val) { std::cout << "int " << val << '\n'; },
        [](double val) { std::cout << "double " << val << '\n'; },
        [](std::string val) { std::cout << "std::string " << val << '\n'; }
    };

    auto twiceVariant = Overload{
        [](auto & val) { val = val * 2; },
        [](std::string & val) { val = val + " " + val; }
    };

    std::variant<int, double, std::string> vval{54};
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);

    vval = 65.67;
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);    
    
    vval = "Using Overloaded Lambdas as Visitors";
    std::visit(displayVariant, vval);
    std::visit(twiceVariant, vval);
    std::visit(displayVariant, vval);
    }

    return 0;
}

/*********
    END OF FILE
************/




