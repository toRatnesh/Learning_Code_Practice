/*****

References

        Programming with C++20 | Andreas Fertig
        https://en.cppreference.com/w/cpp/utility/format.html
        https://en.cppreference.com/w/cpp/utility/format/spec.html

Chapter 5 | std::format Modern & typesafe text formatting

5.6 Writing our own logging function

5.6.1 Prefer make_format_args when forwarding an argument pack

    1.  use std::make_format_args to create a type-erased wrapper
    2.  pass the result of std::make_format_args to std::vformat or one of its alternatives (e.g. std::vformat_to)

5.6.2 Create the format specifier at compiletime
    
    instead of passing format string every time we can build it and pass only arguments which we want to log

5.6.3 Formatting the time
    we can format time point using std::format

**********/

#include <format>
#include <iostream>
#include <string_view>
#include <chrono>

enum log_level { FATAL, WARNING, INFO, DEBUG };

using log_level_t = enum log_level;

// custom formatter for log_level_t
template <>
struct std::formatter<log_level_t> : std::formatter<const char*> {
    static constexpr const char* log_level_str[]{"FATAL", "WARNING", "INFO",
                                                 "DEBUG"};
    // parse is inherited from std::formatter<const char*>, since we don't need
    // custom format specifier we don't need to write our own

    auto format(const log_level_t level, std::format_context& ctx) const {
        return std::formatter<const char*>::format(log_level_str[level], ctx);
    }
};

void vlog(const log_level_t level,
        const std::string_view fmt,
         std::format_args && args) {

    /*  
        Type erased version of the arguments
    */
    std::cout << std::format("{} | ", level)
              << std::vformat(fmt, args) << '\n';

}


constexpr void log(const log_level_t level,
        const std::string_view fmt,
         const auto&... args) {
    /* Drawback:
        for every combination of args, a new log function is created by the
       compiler and a std::format counterpart as well this makes inline
       impossible
    */

    // std::cout << std::format("{}", level) << std::format(fmt, args...) << '\n';

    //std::cout << std::format("{} | ", level)
    //          << std::vformat(fmt, std::make_format_args(args...)) << '\n';

    vlog(level, fmt, std::make_format_args(args...));
}


template<size_t Args>
constexpr auto make_fmt() {
    constexpr std::string_view abrace{"{} "};
    constexpr auto abrace_size = abrace.size();

    std::array<char, Args * abrace_size> braces{};

    auto i{0u};
    std::for_each_n(braces.begin(), braces.size(), [&](auto & element) {
        element = abrace[i % abrace_size];
        ++i;
    });

    return braces;
}


constexpr void log2(const log_level_t level,
         const auto&... args) {
    /* Drawback:
        for every combination of args, a new log function is created by the
       compiler and a std::format counterpart as well this makes inline
       impossible
    */

    // std::cout << std::format("{}", level) << std::format(fmt, args...) << '\n';

    //std::cout << std::format("{} | ", level)
    //          << std::vformat(fmt, std::make_format_args(args...)) << '\n';

    constexpr auto fmt = make_fmt<sizeof...(args)>();

    vlog(level, std::string_view(fmt.data(), fmt.size()), std::make_format_args(args...));
}

int main() {

    {
        std::cout << std::format("=== 5.6.1 Prefer make_format_args when forwarding an argument pack ===\n");

        {
            log(DEBUG, "{} {}", "using custom log function in C++", 20);
        }

        {
            const std::string_view fmt{"{} {}"};
            log(DEBUG, fmt, "using custom log function in C++", 20);
        }
    }

    {
        std::cout << std::format("\n=== 5.6.2 Create the format specifier at compiletime ===\n");
        {
            log2(DEBUG, "using custom log function in C++", 20);
        }
    }

    {
        std::cout << std::format("\n=== 5.6.3 Formatting the time ===\n");

        const auto now = std::chrono::system_clock::now();
        std::clog << std::format("[{:%Y-%m-%d-%H:%M:%S}] ", now) << '\n';

    }

    return 0;
}

/*****
    END OF FILE
**********/
