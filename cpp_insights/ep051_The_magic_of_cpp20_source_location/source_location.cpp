/*****

ep051_The_magic_of_cpp20_source_location

References
episode https://www.youtube.com/watch?v=rYI4guK7D_8
https://en.cppreference.com/w/cpp/utility/source_location

std::source_location class represents certain information about 
the source code, such as file names, line numbers, and function names

Field access
line			return the line number represented by this object
column			return the column number represented by this object
file_name		return the file name represented by this object
function_name	return the name of the function represented by this object, if any

**********/

#include <print>
#include <source_location>

void LOG_ERROR(const char * msg, const char * file, const char * func, auto lineno) {
    std::println("[{} {} {}] {}", file, func, lineno, msg);
}

#define ERROR(msg) LOG_ERROR(msg, __FILE__, __func__, __LINE__)

void LOG_MSG(const char * msg, const std::source_location location = std::source_location::current()) {
    std::println("[{} {} {}] {}", location.file_name(), location.function_name(), location.line(), msg);
}

int main() {
    
    ERROR("Log without std::source_location");
    
    LOG_MSG("Log with std::source_location");

    return 0;
}

/*****
    END OF FILE
**********/

