/*****

Reference
    CppCon 2022 - Lightning Talk: Ref, C++ const ref, immutable ref? - Francesco Zoffoli
    https://www.youtube.com/watch?v=OupN6FMZbmA

Ref:
    access and modification allowed

const Ref
    access allowed, modification not allowed from where const ref is present
    Drawback:
        data may be modified through const_cast<>
        some other function may modify data

Immutable Ref
    access allowed, no one can modify data

**********/

#include <iostream>

template<typename T>
class Immutable {
    const T data;
    
    public:
    template<typename ... Args>
    Immutable(Args && ... args) 
    : data(static_cast<Args&&>(args)...) { }
    
    operator int() {
        return data;
    }
};

int using_ref(int & arg) {
    std::cout << "using_ref, data " << arg << '\n';
    arg += 10;
    std::cout << "using_ref, data " << arg << '\n';
    return arg;
}

int using_const_ref(const int & arg) {
    std::cout << "using_const_ref, data " << arg << '\n';
    //arg += 10;  // error: assignment of read-only reference 'arg'

    const_cast<int &>(arg) += 10;

    using_ref(const_cast<int &>(arg));

    std::cout << "using_const_ref, data " << arg << '\n';
    return arg;
}

Immutable<int> using_imut_ref(Immutable<int> & arg) {
    std::cout << "using_imut_ref, data " << arg << '\n';

    std::cout << "using_imut_ref, data " << arg << '\n';
    return arg;
}

int main() {
    int data = 10;
    { int retval = using_ref(data); }
    { int retval = using_const_ref(data); }
    {
        Immutable<int> val{data};
        Immutable<int> retval = using_imut_ref(val); 
    }

    return 0;
}


/*****
    END OF FILE
**********/



