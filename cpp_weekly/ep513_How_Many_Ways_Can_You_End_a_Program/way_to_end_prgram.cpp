/*****

References
    episode:    https://www.youtube.com/watch?v=pwf45vaXm3Q
    
    https://en.cppreference.com/w/cpp/utility/program/exit.html
    https://cppreference.com/w/c/program/_Exit.html
    https://en.cppreference.com/w/cpp/keyword/return.html
    https://en.cppreference.com/w/cpp/utility/program/abort.html
    https://en.cppreference.com/w/cpp/error/terminate.html
    https://man7.org/linux/man-pages/man3/pthread_exit.3.html

_Exit
    Causes normal program termination to occur without completely cleaning the resources.
    Destructors of variables with automatic, thread local and static storage durations are not called. 
    Functions passed to std::at_quick_exit() or std::atexit() are not called. 
    Whether open resources such as files are closed is implementation defined.

 _exit()
    Terminates the calling process "immediately".
    Any open file descriptors belonging to the process are closed.
    Any children of the process are inherited by init(1) (or by the nearest "subreaper" 
    process as defined through the use of the prctl(2) PR_SET_CHILD_SUBREAPER operation).
    The process's parent is sent a SIGCHLD signal.

abort
    Causes abnormal program termination unless SIGABRT is being caught by a signal handler passed to std::signal and the handler does not return.
    Destructors of variables with automatic, thread local(since C++11) and static storage durations are not called.
    Functions registered with std::atexit() and std::at_quick_exit(since C++11) are also not called.
    Whether open resources such as files are closed is implementation defined.

exit
    Until C++11
    Objects with static storage duration are destroyed and functions registered by calling std::atexit are called:

    Since C++11
    The destructors of objects with thread local storage duration that are associated with the current thread, 
    the destructors of objects with static storage duration, and the functions registered with std::atexit are executed concurrently, 

    All C streams are flushed and closed.
    Files created by std::tmpfile are removed.

**********/

#include <iostream>
#include <format>
#include <thread>
#include <exception>
#include <unistd.h>

class S{
    std::string m_data;
    public:
    S(std::string data) : m_data{data} { std::cout << "Cx " << m_data << '\n'; }
    ~S() { std::cout << "Dx " << m_data << '\n'; }

    S(const S &) { std::cout << "copy " << m_data << '\n'; }
    S(S &&) { std::cout << "move " << m_data << '\n'; }

    S& operator=(const S &) { std::cout << "copy= " << m_data << '\n'; return *this; }
    S& operator=(S &&) { std::cout << "move= " << m_data << '\n'; return *this; }

};

/*
int callback(S && ) {

    exit(0);
}
*/

S s{"global"};

int main()
{
    S ls{"local"};
    static S ss{"static"};
    thread_local S tls{"thread local"};

    //std::jthread th(&callback, S{});

    return 0;         // returns calls all destructor

    //exit(0);

    //_Exit(0);

    //_exit(0);

    //std::terminate();
    
    //abort();

}

/*****
    END OF FILE
**********/

