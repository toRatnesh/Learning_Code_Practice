/*****

References
    Anthony Williams - C++ Concurrency in Action

3.2 Protecting shared data with mutexes
    mutex (mutual exclusion)
        You could mark all the pieces of code that access the data structure as mutually exclusive, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished
        Mutexes also has issue of deadlock and protecting either too much or too little data

3.2.2 Structuring code for protecting shared data

    In case we are returning a pointer or reference to the shared date member, using mutex protection is of no use.

    As long as none of the member functions return a pointer or reference to the protected data to their caller either via their return value or via an out parameter, the data is safe.
    It’s also important to check that they don’t pass these pointers or references in to functions they call that aren’t under your control
    Don’t pass pointers and references to protected data outside the scope of the lock, whether by returning them from a function, storing them in externally visible memory, or passing them as arguments to user-supplied functions

**********/

#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class Data {
    std::string     m_data;

   public:
    void set(std::string str) { m_data = str; }
    std::string get() { return m_data; }
    size_t get_size() { return m_data.size(); }
};

class DataWrapper {
    Data        data;
    std::mutex   data_mutex;

    public:

    template<typename Callable>
    void processData(Callable callable) {
        std::lock_guard     lg(data_mutex);
        callable(data);
    }

    void add(DataWrapper & data_wrap) {
        std::lock_guard     lg(data_mutex);
        data.set(data_wrap.data.get());
    }
};

Data * unprotected_data;

void set_unprotected_data(Data & data) {
    // unprotected_data can be accessed wihtou mutex
    unprotected_data = &data;
}

void use_unprotected_data() {
    unprotected_data->set("using unprotected data");
    std::cout << unprotected_data->get() << '\n';
}

int main() {
    DataWrapper dw;
    dw.processData(set_unprotected_data);

    unprotected_data->set("sample string");
    std::cout << unprotected_data->get() << '\n';

    std::thread thr(use_unprotected_data);

    unprotected_data->set("some other string");
    std::cout << unprotected_data->get() << '\n';

    thr.join();

    return 0;
}

/*****
    END OF FILE
**********/



