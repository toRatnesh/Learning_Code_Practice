/*****

References

    episode https://www.youtube.com/watch?v=-oSuITjrzgU

    This example demonstrates about how to display variant value in easiest way

**********/

#include <print>
#include <string>
#include <variant>

struct DisplayLambda {
    auto operator()(const auto & val) {
        std::println("{}", val);
    }
};

void displayVariant(const auto & val) {
    DisplayLambda display;
    if(std::holds_alternative<int>(val)) {
        display(std::get<int>(val));
    } else if(std::holds_alternative<double>(val)) {
        display(std::get<double>(val));
    } else if(std::holds_alternative<std::string>(val)) {
        display(std::get<std::string>(val));
    }
}

std::variant<int, double, std::string> get_variant_value(const int val) {
    switch(val) {
        case 1: return 42;
        case 2: return 3.14;
        case 3: return "a string";
    }

    return 0;
}

int main() {
    std::println("=== variant value display using std::visit ===");
    std::visit([](const auto & val) {
        std::println("{}", val);
    }, get_variant_value(1));

    std::visit([](const auto & val) {
        std::println("{}", val);
    }, get_variant_value(2));

    std::visit([](const auto & val) {
        std::println("{}", val);
    }, get_variant_value(3));

    std::println("=== variant value display using lambda ===");
    displayVariant(get_variant_value(1));
    displayVariant(get_variant_value(2));
    displayVariant(get_variant_value(3));
    
    return 0;
}

/*****
    END OF FILE
**********/

