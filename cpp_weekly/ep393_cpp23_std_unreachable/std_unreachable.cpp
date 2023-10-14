/*****

References
    episode https://www.youtube.com/watch?v=ohMyb4jPIAQ
    https://en.cppreference.com/w/cpp/utility/unreachable

std::unreachable
    Invokes undefined behavior. 
    An implementation may use this to optimize impossible code branches away (typically, in optimized builds) or 
    to trap them to prevent further execution (typically, in debug builds).

**********/

#include <iostream>
#include <utility>

enum class MSG_TYPE {SEND, RECV, WAIT, NOT_HANDLE};

std::string process_msg(MSG_TYPE msg_type) {    
    switch(msg_type) {
        case MSG_TYPE::SEND:
            return std::string("sending message");
        case MSG_TYPE::RECV:
            return std::string("receiving message");
        case MSG_TYPE::WAIT:
            return std::string("waiting for message");
        default:
            std::unreachable();
    }
}

std::string improved_process_msg(MSG_TYPE msg_type) {    
    // DO NOT USE default THIS WILL GENERATE ERROR/WARNING IF AN OPTION IS NOT HANDLED
    switch(msg_type) {
        case MSG_TYPE::SEND:
            return std::string("sending message");
        case MSG_TYPE::RECV:
            return std::string("receiving message");
        case MSG_TYPE::WAIT:
            return std::string("waiting for message");
    }
    std::unreachable();
}

int main() {
    {
        std::string msg = process_msg(MSG_TYPE::SEND);
        std::cout << msg << '\n';
    }
    {
        std::string msg = process_msg(MSG_TYPE::NOT_HANDLE);
        std::cout << msg << '\n';
    }
    {
        std::string msg = improved_process_msg(MSG_TYPE::NOT_HANDLE);
        std::cout << msg << '\n';
    }
    return 0;
}

/*****
    END OF FILE
**********/



