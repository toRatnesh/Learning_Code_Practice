/*****

References
    Effective Modern C++ | Scott Meyers


Item 6: Use the explicitly typed initializer idiom when auto deduces undesired types

Consider a function that takes a Widget and returns a std::vector<bool>, 
where each bool indicates whether the Widget offers a particular feature:

std::vector<bool> features(const Widget& w);

Calling features like

bool highPriority = features(w)[5];

operator[] returns a std::vector<bool>::reference object, which is then 
implicitly converted to the bool that is needed to initialize highPriority

Calling it like

auto highPriority = features(w)[5];

because auto deduces that as the type of highPriority
The value it does have depends on how std::vector<bool>::reference is implemented


"invisible" proxy classes don’t play well with auto
Objects of such classes are often not designed to live longer than a single statement
You therefore want to avoid code of this form:

auto someVar = expression of "invisible" proxy class type;


The solution is to force a different type deduction, using the explicitly typed initializer idiom.
auto highPriority = static_cast<bool>(features(w)[5]);

Summary:
    -> "Invisible" proxy types can cause auto to deduce the “wrong” type for an initializing expression.
    -> The explicitly typed initializer idiom forces auto to deduce the type you want it to have.

**********/

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

std::vector<bool> getFeatures() {
    return {true, false, true, false, true, true};
}

int main() {

    {
        bool feature = getFeatures()[0];
        std::cout << std::boolalpha << feature << '\n';
    }
    
    {
        auto feature = getFeatures()[1];
        std::cout << std::boolalpha << feature << '\n';       
    }

    return 0; 
}

/*****
    END OF FILE
**********/

