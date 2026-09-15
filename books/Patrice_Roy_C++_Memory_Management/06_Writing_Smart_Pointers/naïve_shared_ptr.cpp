/*****

References
    C++ Memory Management | Patrice Roy
    https://en.cppreference.com/cpp/memory/shared_ptr

Chapter 6 | Writing Smart Pointers

3. Writing your own (naïve) shared_ptr
    A shared_ptr<T> type is a difficult beast to implement and a harder beast yet to optimize.

    template< class T > 
    class shared_ptr;

    The main difficulty when writing a shared_ptr is that it’s a type with two responsibilities: 
    it co-owns both the pointee and the usage counter, requiring some measure of care, 
    especially with respect to exception safety.

    Note that our shared counter is a pointer to an atomic integral since 
    shared_ptr<T> is particularly relevant in multithreaded cases where 
    one does not know which of the threads will be the last user of the object.

    .   By default, we will define shared_ptr<T> to be empty, 
        thus conceptually equivalent to a null pointer.

    .   constructor of shared_ptr<T> that takes T* as an argument represents 
        the act of taking ownership of the pointee. For that reason, 
        if an exception is thrown when allocating the counter, 
        that pointee is destroyed.

    .   copy constructor will represent sharing ownership of the pointee, 
        making sure to consider the case where the source object models a null pointer.

    .   move constructor models the transfer of ownership. 
        As is often the case for move operations, 
        it’s very fast and it shows highly predictable behavior.

    .   copy assignment models the act of releasing control of the currently 
        held resource and sharing the resource of its argument

    .   move assignment models the act of releasing control of the currently 
        held resource and transferring control of the resource held by 
        the argument to the assigned-to object

    .   Destruction make sure that the last owner of the pointee destroys it, to avoid immortal objects. 
        The key point is that shared_ptr<T> should only destroy the pointed-to 
        T object if it was the last user of that object.

Other member functions

    operator== and operator!=
    operator*() and operator->()
    get()

A few words on make_shared()
    Why make_shared()?
    make_shared<T>(), this factory function is responsible for allocating 
    both the T object and the counter, perfectly forwarding the arguments 
    received by the function to the T constructor

    Since the same function performs both allocations, 
    it can fuse them in a single allocation of a memory block 
    that contains both the T object and the counter, 
    putting them both on the same cache line

**********/

#include <iostream>
#include <memory>
#include <utility>
#include <atomic>

struct Data {
    std::string     sdata{};
    int             idata{};
};

namespace nonstd {

    template<typename T>
    class shared_ptr
    {

        T   * mptr{nullptr};
        std::atomic<uint64_t>    *mpcnt{nullptr};

        void swap(shared_ptr & other) {
            std::swap(mptr, other.mptr);
            std::swap(mpcnt, other.mpcnt);
        }

        public:

        ~shared_ptr() { 
            if(mpcnt) {

                auto l_expected = mpcnt->load();
                auto l_desired = l_expected - 1;

                while(not mpcnt->compare_exchange_weak(l_expected, l_desired)) {
                    l_desired = l_expected - 1;
                }

                if(l_desired == 0) {

                    delete mptr;
                    mptr = nullptr;

                    delete mpcnt;
                    mpcnt = nullptr;
                }
            }
        }

        shared_ptr() : mptr{nullptr} { }
        shared_ptr(T * data) : mptr{data} {     
            if(mptr) {
                try {
                    mpcnt = new std::atomic<uint64_t>{1};
                } catch(...) {
                    delete mptr; mptr = nullptr;
                    throw;
                } 
            }
        }

        shared_ptr(const shared_ptr & other) 
        : mptr{other.mptr}, mpcnt{other.mpcnt} {
            if(mpcnt) {
                ++(*mpcnt);
            }
        }

        shared_ptr& operator=(const shared_ptr & other)  {
            shared_ptr{other}.swap(*this);
            return *this;
        }

        shared_ptr(shared_ptr && other ) 
        :   mptr{std::exchange(other.mptr, nullptr)},
            mpcnt{std::exchange(other.mpcnt, nullptr)}
        { }

        shared_ptr& operator=(shared_ptr && other ) {
            std::shared_ptr{std::move(other)}.swap(*this);
            return *this;
        }

        operator bool() { return mptr != nullptr; }

        bool operator==(const shared_ptr & other) const {
            return (mptr == other.mptr);
        }

        bool operator!=(const shared_ptr & other) const {
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
        std::cout << "=== using std shared pointer ===\n";


        std::shared_ptr<Data>   np{};
        if(np) {
            std::cout << np->sdata << ", " << np->idata << '\n';        
        }

        std::shared_ptr<Data>   pdata(new Data{"data-1", 1});
        std::shared_ptr<Data>   cpdata(pdata);    // use of delted copy constructor
        std::shared_ptr<Data>   mpdata(std::move(pdata));

        std::cout << cpdata->sdata << ", " << cpdata->idata << '\n';
        std::cout << (*cpdata).sdata << ", " << (*cpdata).idata << '\n';

        std::cout << mpdata->sdata << ", " << mpdata->idata << '\n';
        std::cout << (*mpdata).sdata << ", " << (*mpdata).idata << '\n';

        Data * rawp = mpdata.get();
        std::cout << rawp->sdata << ", " << rawp->idata << '\n';
    }

    {
        std::cout << "\n=== using naïve shared pointer ===\n";

        nonstd::shared_ptr<Data>   np{};
        if(np) {
            std::cout << np->sdata << ", " << np->idata << '\n';        
        }

        nonstd::shared_ptr<Data>   pdata(new Data{"data-1", 1});
        nonstd::shared_ptr<Data>   cpdata(pdata);    // use of delted copy constructor
        nonstd::shared_ptr<Data>   mpdata(std::move(pdata));

        std::cout << cpdata->sdata << ", " << cpdata->idata << '\n';
        std::cout << (*cpdata).sdata << ", " << (*cpdata).idata << '\n';

        std::cout << mpdata->sdata << ", " << mpdata->idata << '\n';
        std::cout << (*mpdata).sdata << ", " << (*mpdata).idata << '\n';
        
        Data * rawp = mpdata.get();
        std::cout << rawp->sdata << ", " << rawp->idata << '\n';
    }

}

/*****
    END OF FILE
**********/


