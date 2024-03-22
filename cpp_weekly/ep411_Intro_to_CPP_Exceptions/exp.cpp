/*****

    std::exception

    NOTE:
    -> Compilers are very bad at optimizing around exception
    -> generaly catch by const &
    -> catch blocks are handled in the order they are declared
    -> exception catch block works with polymorphism to choose 
        the most correct derived type of handler

    For more info visit
    episode https://www.youtube.com/watch?v=uE0h79vB-rw
    https://en.cppreference.com/w/cpp/error/exception

**********/

#include <print>

// Lippincott function for centralized exception handling
void handle_exception() {
    std::print("Exception: ");
    try {
        throw;
    } catch(const int & exp) {
        std::println("int exception {}", exp);
    }
    /*
    catch(const std::exception & exp) {
        std::println("{}", exp.what());
    } 
    // warning: exception of type 'std::runtime_error' will be caught by earlier handler
    */
    catch(const std::runtime_error & exp) { 
        std::println("{}", exp.what());
    } 
    /*
    catch (...) {   // error: '...' handler must be the last handler for its try block

    }*/ 
    catch(const std::exception & exp) {
        std::println("{}", exp.what());
    } 
    catch (...) {
        std::println("Unknown exception");
    }
}

void throw_exception(bool flag) {
    if(flag) {
        throw std::runtime_error("Throwing run time error");
    }
    std::println("Learning Exception");
}

int main() {
    try {
        throw_exception(false);
        throw_exception(true);
    } catch (...) {
        handle_exception();
    }
    return 0;
}

/*****
    END OF FILE
**********/


