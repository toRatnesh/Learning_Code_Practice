/*****

References

    episode https://www.youtube.com/watch?v=k1I4ZoB50_I
    https://en.cppreference.com/w/cpp/language/constraints
    https://en.cppreference.com/w/cpp/language/requires
    https://en.cppreference.com/w/cpp/language/constraints#Requires_clauses

requires expression
    Yields a prvalue expression of type bool that describes the constraints.

    constant expression that returns a boolean 
    retruns true if the code is valid

requires clauses
    The keyword requires is used to introduce a requires clause, 
    which specifies constraints on template arguments or on a function declaration.

    The keyword requires must be followed by some constant expression (so it's possible to write requires true), 
    but the intent is that a named concept (as in the example above) or 
    a conjunction/disjunction of named concepts or a requires expression is used.


    constraints function and classes (all templates)
    eliminate the function from the overload set if there's no valid match

**********/

#include <iostream>
#include <format>
#include <string>

template<typename T>
constexpr bool can_increment() {
    return requires(T t) {++t;};
}

template<typename T>
requires requires(T t) {++t;}   // this is adhoc concept and is a code smell
auto increment_it(T t) {
    return ++t;
}

template<typename T>
concept can_pre_increment = requires(T t) {++t;};

template<typename T>
requires can_pre_increment<T>
auto improved_increment_it(T t) {
    return ++t;
}

struct Person {
    std::string name;
    int         age;
};

int main() {

    std::cout << std::format("can_increment<int>() {}", can_increment<int>()) << '\n';
    std::cout << std::format("can_increment<const int>() {}", can_increment<const int>()) << '\n';
    std::cout << std::format("can_increment<std::string>() {}", can_increment<std::string>()) << '\n';

    int ival = 2;
    std::string sval("sample string");

    std::cout << std::format("increment_it(ival) {}", increment_it(ival)) << '\n';
    //std::cout << std::format("increment_it<const int>(ival) {}", increment_it<const int>(ival)) << '\n'; // CE error: no matching function for call to 'increment_it'
    //std::cout << std::format("increment_it(sval}) {}", increment_it(sval)) << '\n'; // CE error: no matching function for call to 'increment_it'
    

    std::cout << std::format("improved_increment_it(ival) {}", improved_increment_it(ival)) << '\n';
    //std::cout << std::format("improved_increment_it<const int>(ival) {}", improved_increment_it<const int>(ival)) << '\n'; // CE error: no matching function for call to 'improved_increment_it'
    //std::cout << std::format("improved_increment_it(sval}) {}", improved_increment_it(sval)) << '\n'; // CE error: no matching function for call to 'improved_increment_it'

    return 0;
}

/*****
    END OF FILE
**********/

