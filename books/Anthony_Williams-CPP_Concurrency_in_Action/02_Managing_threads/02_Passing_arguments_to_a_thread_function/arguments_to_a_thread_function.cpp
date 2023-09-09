/*******

References
    Anthony Williams - C++ Concurrency in Action

2 Managing threads

    The C++ Standard Library makes most thread-management tasks relatively easy, 
    with almost everything managed through the std::thread object associated with a given thread.

2.2 Passing arguments to a thread function

    By default, the arguments are copied into internal storage, where they can be accessed by the newly created thread of execution, and then passed to the callable object or function as rvalues as if they were temporaries.

    Wrap the arguments that need to be references in std::ref

    You can pass a member function pointer as the function, provided you supply a suitable object pointer as the first argument
    You can also supply arguments to such a member function call: the third argument to the std::thread constructor will be the first argument to the member function, and so forth.

    For supplying arguments is where the arguments can’t be copied but can only be moved: the data held within one object is transferred over to another, leaving the original object empty.
    Where the source object is temporary, the move is automatic, but where the source is a named value, the transfer must be requested directly by invoking std::move().

***********/

#include <iostream>
#include <thread>
#include <string>
#include <stdexcept>
#include <memory>

class Student {
    std::string     m_name;
    public:
    Student(std::string name) : m_name(name) { }

    void display(std::string subject) {
        std::cout << m_name << " will study " << subject << '\n';
    }
    void display_with_const_ref(std::string const & subject) {
        std::cout << m_name << " will study " << subject << '\n';
    }
    void display_with_ref(std::string & subject) {
        std::cout << m_name << " will study " << subject << '\n';
    }    
};

void fun_with_only_movable_parm(std::unique_ptr<std::string> up_string) {
    std::cout << "Function taking std::unique_ptr<std::string> as parm: " << *up_string << '\n';
}

int main() {

    std::cout << "=== Passing member function as thread routine ===\n";
    {
        Student stu("Student - 01");
        std::string sub("Physics");
        std::thread thr(&Student::display, stu, sub);
        thr.join();
    }
    {
        Student stu("Student - 01");   
        std::thread thr(&Student::display, stu, std::string("Physics"));
        thr.join();
    }

    {
        Student stu("Student - 02");
        std::string sub("Chemistry");
        std::thread thr(&Student::display_with_const_ref, stu, sub);
        thr.join();
    }
    {
        Student stu("Student - 02");
        std::thread thr(&Student::display_with_const_ref, stu, std::string("Chemistry"));
        thr.join();
    }


    std::cout << "\n=== Using std::ref for references ===\n";
    {
        Student stu("Student - 03");
        std::string sub("Math");
        
        // CE static assertion failed: std::thread arguments must be invocable after conversion to rvalues
        //std::thread thr(&Student::display_with_ref, stu, sub);    // an rvalue can not bind to non-const ref
        
        std::thread thr(&Student::display_with_ref, stu, std::ref(sub));
        thr.join();
    }
    {
        Student stu("Student - 03");
        
        //  can not pass reference to temporary

        // CE error: static assertion failed: std::thread arguments must be invocable after conversion to rvalues
        //std::thread thr(&Student::display_with_ref, stu, std::string("Math"));    // an rvalue can not bind to non-const ref
        
        // CE error: use of deleted function 'void std::ref(const _Tp&&) [with _Tp = __cxx11::basic_string<char>]'
        //std::thread thr(&Student::display_with_ref, stu, std::ref(std::string("Math")));
        //thr.join();
    }


    std::cout << "\n=== Using arguments which can not be copied \n";
    {
        auto up = std::make_unique<std::string>("This will need to be moved explicitly");
        //std::thread thr(fun_with_only_movable_parm, up);   // CE because unique pointer can not be copied
        std::thread thr(fun_with_only_movable_parm, std::move(up));
        thr.join();
    }

    {
        std::thread thr(fun_with_only_movable_parm, std::make_unique<std::string>("Temporary will be moved automatically"));
        thr.join();
    }

    return 0;
}

/*******
	END OF FILE
***********/


