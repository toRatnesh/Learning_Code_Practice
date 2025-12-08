/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html#Designated_initializers
    https://en.cppreference.com/w/cpp/language/list_initialization.html

Chapter 8 | Aggregates: Designated initializers and more

8.4 Class Template Argument Deduction for aggregates

.   since C++ 17 CTAD is supported by default only for classes
.   since C++20 CTAD is also supported for aggregates

**********/

#include <iostream>
#include <format>
#include <string>

struct Error {
    int errorno;
    std::string errorstr;
};

template<typename R> 
struct ReturnVal {
    R rval;
    Error error;
};

auto raiseAlarm(const std::string alarm, const bool f) {

    if(f) {
        std::cout << "Raising alarm: " << alarm << '\n';
        return ReturnVal{true, {0, ""}};    
    }

    return ReturnVal{false, {1, "alarm does not exist"}};
}

int main() {

    {
        const auto [rval, error] = raiseAlarm("Alarm-01", true);
        if(not rval) {
            std::cout << std::format("Error code: {} description: {}\n", error.errorno, error.errorstr);
        }
    }

    {
        const auto [rval, error] = raiseAlarm("Alarm-01", false);
        if(not rval) {
            std::cout << std::format("Error code: {} description: {}\n", error.errorno, error.errorstr);
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/
