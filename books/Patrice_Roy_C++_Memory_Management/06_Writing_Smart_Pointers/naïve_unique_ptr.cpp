/*****

References
    C++ Memory Management | Patrice Roy
    https://en.cppreference.com/cpp/memory/unique_ptr

Chapter 6 | Writing Smart Pointers


2. Writing your own (naïve) unique_ptr

Type signature

    template<class T, class Deleter = std::default_delete<T>> 
    class unique_ptr;                   // (1)	(since C++11)   for scalar type

    template <class T, class Deleter> 
    class unique_ptr<T[], Deleter>;     // (2)	(since C++11)   for array type
    
    The next step will be to choose the form of unique_ptr<T,D>. 
    We will expect most deleters to be stateless and use empty base optimization (EBO) 
    to our advantage by deriving from our deleter type.

Special member functions

    The code for the special member functions will be 
    the same for both the scalar and the array forms of unique_ptr.

    copy ✗
    move ✓
    both the general case and the array case, 
    operator bool() (true only if the object does not model a null pointer), 
    empty() (true only if the object does model a null pointer), 
    operator==() and operator!=()

    get() in both its const and non-const versions in order to expose the underlying pointer

Pointer-like functions
    For pointer-to-scalar, we will want to implement operator*() and operator->()

    The operator->() member function is a strange beast: when used on an object, 
    it will be reinvoked on the returned object (and again on that returned object, and so on) 
    until something returns a raw pointer, at which point the compiler will know what to do. 
    It’s a very powerful mechanism.
    
    C++23 introduces the “deduced this” mechanism that allows one to explicitly mark 
    the first argument of a member function with the this keyword. 
    Doing so and combining it with a forwarding reference (the U&& type) 
    lets the compiler deduce the const-ness (or lack thereof) of this, in effect, 
    expressing both the const and non-const versions in a single function.


This example demonstrates implementation of a naïve unique_ptr
    
**********/

#include <iostream>
#include <memory>
#include <utility>

struct Data {
    std::string     sdata{};
    int             idata{};
};

namespace nonstd {


    // START - deleter wrapper and default deleter 
    // deleter must be stateless

    template<typename T>
    struct deleter_wrapper {
        using deleter_fp = void(*)(T *);
        deleter_fp  mdfun;
        
        deleter_wrapper(deleter_fp dfun) : mdfun{dfun} {}
        void operator()(T * ptr) { mdfun(ptr); }
    };

    template<typename T>
    struct default_deleter {
        void operator()(T * ptr) const { delete ptr; }
    };
    
    template<typename T>
    struct default_deleter<T[]> {
        void operator()(T * ptr) const { delete[] ptr; }
    };  

    // END - deleter

    // START - type traits to check for deleter
    template<typename T>
    struct is_deleter_funcion : std::false_type { };

    template<typename T>
    struct is_deleter_funcion<void (*)(T *)> : std::true_type { };

    template<typename T>
    constexpr auto is_deleter_funcion_v = is_deleter_funcion<T>::value;

    // END - type traits

    template<typename T, class D = default_deleter<T>>
    class unique_ptr : std::conditional_t<
        is_deleter_funcion_v<T>, deleter_wrapper<T>, D
    >
    {
        using deleter_type = std::conditional_t<is_deleter_funcion_v<T>, deleter_wrapper<T>, D>;

        T   * mptr{nullptr};

        void swap(unique_ptr & other) {
            std::swap(mptr, other.mptr);
        }

        public:

        ~unique_ptr() { 
            if(mptr) {

                //delete mptr;
                //mptr = nullptr;

                // WHY STATIC CAST?
                // CAST 'this' POINTER TO ITS BASE DELETER TYPE
                // AND THEN INVOKE THE FUNCTION CALL OPERATOR OF
                // THE DELETER WHICH TAKES THE POINTER AS A PARAMETER
                (*static_cast<deleter_type *>(this))(mptr);
                mptr = nullptr;


            }
        }

        unique_ptr() : mptr{nullptr} { }
        unique_ptr(T * data) : mptr{data} { }

        unique_ptr(const unique_ptr & ) = delete;
        unique_ptr& operator=(const unique_ptr & ) = delete;

        unique_ptr(unique_ptr && other ) : mptr{std::exchange(other.mptr, nullptr)} { }
        unique_ptr& operator=(unique_ptr && other ) {
            std::unique_ptr{std::move(other)}.swap(*this);
            return *this;
        }

        operator bool() { return mptr != nullptr; }

        bool operator==(const unique_ptr & other) {
            return (mptr == other.mptr);
        }

        bool operator!=(const unique_ptr & other) {
            return not(*this == other);
        }

#ifdef __cpp_explicit_this_parameter

        // C++ 23 DEDUCING this

        template<typename U>
        decltype(auto) operator*(this U && self) { return *(self.mptr); }
        
        template<typename U>
        decltype(auto) operator->(this U && self) { return self.mptr; }
        
        template<typename U>
        decltype(auto) get(this U && self) { return self.mptr; }
    
#else 

        T& operator*() { return *mptr; }
        const T& operator*() const { return *mptr; }

        T* operator->() { return mptr; }
        const T* operator->() const { return mptr; }

        T* get() { return mptr; }
        const T* get() const { return mptr; }
#endif

    };
}

int main() {

    {
        std::cout << "=== using std unique pointer ===\n";

        auto l_data_deleter = [](Data * dp) { delete dp; dp = nullptr;};
        std::unique_ptr<Data, decltype(l_data_deleter)>   np{nullptr, l_data_deleter};
        if(np) {
            std::cout << np->sdata << ", " << np->idata << '\n';        
        }

        std::unique_ptr<Data, decltype([](Data * dp) { delete dp; dp = nullptr;})>   pdata(new Data{"data-1", 1});
        //std::unique_ptr<Data>   cpdata(pdata);    // use of delted copy constructor
        //std::unique_ptr<Data, decltype([](Data * dp) { delete dp; dp = nullptr;})>   mpdata(std::move(pdata));    // move is not allowed because creating a different type
        
        auto   mpdata(std::move(pdata));
        std::cout << mpdata->sdata << ", " << mpdata->idata << '\n';
        std::cout << (*mpdata).sdata << ", " << (*mpdata).idata << '\n';
                
        Data * rawp = mpdata.get();
        std::cout << rawp->sdata << ", " << rawp->idata << '\n';
    }

    {
        std::cout << "\n=== using naïve unique pointer ===\n";

        nonstd::unique_ptr<Data, decltype([](Data * dp) { delete dp; dp = nullptr;})>   np{};
        if(np) {
            std::cout << np->sdata << ", " << np->idata << '\n';        
        }

        nonstd::unique_ptr<Data, decltype([](Data * dp) { delete dp; dp = nullptr;})>   pdata(new Data{"data-1", 1});
        //nonstd::unique_ptr<Data>   cpdata(pdata);    // use of delted copy constructor
        //nonstd::unique_ptr<Data>   mpdata(std::move(pdata));
        
        auto mpdata(std::move(pdata));
        std::cout << mpdata->sdata << ", " << mpdata->idata << '\n';
        std::cout << (*mpdata).sdata << ", " << (*mpdata).idata << '\n';
        
        Data * rawp = mpdata.get();
        std::cout << rawp->sdata << ", " << rawp->idata << '\n';
    }

}

/*****
    END OF FILE
**********/


