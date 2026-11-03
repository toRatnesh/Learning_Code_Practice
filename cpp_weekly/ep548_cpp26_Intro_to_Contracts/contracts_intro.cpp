/*****

References:
    episode     https://www.youtube.com/watch?v=_H-RfRipIY0
    https://cppreference.com/cpp/header/contracts
    https://cppreference.com/cpp/language/contracts
    Code        https://godbolt.org/z/77oYs3PK6

    Contract assertions allow the programmer to specify properties 
    of the state of the program that are expected to hold at 
    certain points during execution.

    Contract assertions are introduced by function contract specifiers 
    and contract_assert statements. Each contract assertion has a predicate, 
    which is an expression of type bool.

**********/

#include <iostream>
#include <contracts>
#include <exception>

int xdiv1(int n, int d) 
pre(d != 0)
{
    return n/d;
}

int xdiv2(int n, int d) 
{
    contract_assert(d != 0);
    return n/d;
}

bool resource_available() {

    //throw std::runtime_error("Resource is not available");
    

    static bool available{true};

    if(available) {
        available = false;
        return true;
    } else {
        throw std::runtime_error("Resource is not available");
    }

    return false;
    
}

bool processit(const std::string msg) {
    
    contract_assert(resource_available());

    std::cout << "Successfully processed " << msg << '\n';

    return true;
}

int main()
{

    {
        /*
        contract violation in function int xdiv(int, int) at /app/example.cpp:22: d != 0
        [assertion_kind: pre, semantic: enforce, mode: predicate_false, terminating: yes]
        terminate called without an active exception
        Program terminated with signal SIGABRT (6)        
        */ 
        //auto val = xdiv1(10, 0); 
    }

    {
        /*
        contract violation in function int xdiv2(int, int) at /app/example.cpp:29: d != 0
        [assertion_kind: assert, semantic: enforce, mode: predicate_false, terminating: yes]
        terminate called without an active exception
        Program terminated with signal SIGABRT (6)        
        */
        //auto val = xdiv2(10, 0);
    }

    {
        processit("This will be processed");
    }

    {
        processit("This will not be processed");
    }

    return 0;
}

/*****
    END OF FILE
**********/

