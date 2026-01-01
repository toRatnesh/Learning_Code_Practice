/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/enum.html#Using-enum-declaration

Chapter 11 | Language Updates

11.3 using enums

    for pulling all enumerations into the scope of the switch
    As always, be careful with using and be sure to pull only what is really needed

**********/

#include <format>
#include <iostream>
#include <string_view>

enum class LogLevel {
    FATAL,
    WARNING,
    INFO,
    DEBUG
};

constexpr std::string_view to_string(const LogLevel level) {
    /*
    switch(level) {
        case LogLevel::FATAL:
            return "FATAL";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::DEBUG:
            return "DEBUG";                                    
    }
    */

    using enum LogLevel;
    switch(level) {
        case FATAL:
            return "FATAL";
        case WARNING:
            return "WARNING";
        case INFO:
            return "INFO";
        case DEBUG:
            return "DEBUG";                                    
    }    
}

int main() {

    constexpr auto sval = to_string(LogLevel::DEBUG);
    static_assert(sval == std::string_view{"DEBUG"});
    
    std::cout << std::format("{}\n", sval);

    return 0; 
}

/*****
    END OF FILE
**********/

