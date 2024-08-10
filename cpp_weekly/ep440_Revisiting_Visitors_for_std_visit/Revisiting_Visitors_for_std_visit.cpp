/*****

References

    episode https://www.youtube.com/watch?v=et1fjd8X1ho
    https://en.cppreference.com/w/cpp/utility/variant/visit
    https://github.com/toRatnesh/Learning_Code_Practice/blob/main/cpp_weekly/ep134_Inherit_From_Lambdas-Improvement_of_Visitor/improved_visitor.cpp


    This example demonstrates about further about C++ visit  
    which was presented in previous episode 134

**********/

#include <iostream>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

using variant_t = std::variant<int, double, float, std::string, std::string_view>;

std::vector<variant_t> getData() {
    return {23, 23.56, 45.89f, std::string("sample string"), std::string_view("sample string view")};
}

struct Overload {
    void operator()(const int val) const { std::cout << val << ", "; }
    void operator()(const double val) const { std::cout << val << ", "; }
    void operator()(const float val) const { std::cout << val << ", "; }
    void operator()(const std::string val) const { std::cout << val << ", "; }
    void operator()(const std::string_view val) const { std::cout << val << ", ";
    }
};


/*
    Features used in inheritaing operator() from multiple callable
    C++11   Variadic template
    C++17   Variadic using
    C++98   Multiple Inheritence
    C++98   Call Operator Overloading
    C++17   CTAD
    C++20   Able to deduce type without CTAD
*/
template <typename... Callable>
struct OverloadCallable : Callable... {
    using Callable::operator()...;
};

/* // CTAD for OverloadCallable needed pre C++20
template <typename... Callable>
OverloadCallable(Callable ...) -> OverloadCallable<Callable ...>;  // decay_t is not needed because taking params by value
 */


int main() {
    const auto l_data = getData();

    std::cout << "=== Visit using generic lambda ===\n";
    for (const auto& l_elem : l_data) {
        std::visit([](const auto& elem) { std::cout << elem << ", "; }, l_elem);
    }
    std::cout << '\n';

    std::cout << "=== Visit using overloaded operator() ===\n";
    for (const auto& l_elem : l_data) {
        std::visit(Overload{}, l_elem);
    }
    std::cout << '\n';

    std::cout << "=== Visit using inheringted lambda ===\n";
    for (const auto& l_elem : l_data) {
        std::visit(
            OverloadCallable{
                [](const int val) { std::cout << val << ", "; },
                [](const double val) { std::cout << val << ", "; },
                [](const float val) { std::cout << val << ", "; },
                [](const std::string val) { std::cout << val << ", "; },
                [](const std::string_view val) { std::cout << val << ", "; }},
            l_elem);
    }
    std::cout << '\n';

    return 0;
}

/*****
    END OF FILE
**********/



