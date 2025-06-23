/*****

References
    Programming with C++20 | Andreas Fertig

    https://en.cppreference.com/w/cpp/concepts
    https://en.cppreference.com/w/cpp/language/requires

Chapter 1 | Concepts: Predicates for strongly typed generic code

Sadly, when using the template with an unsupported type, finding any error requires a good understanding of the compiler’s error message.
The issue was that we had no way of specifying the requirements to prevent the misuse and at the same time give a clear error message.

1.12 The power of Concepts: requires instead of enable_if

We can use Concepts in more places than enable_if

1.12.1 Call method based in requires

    One thing that gets pretty easy with Concepts is checking whether an object has a certain function.
    With C++20, we can define a concept that has a requires-expression containing a simple requirement.

    template<typename T>
    concept has_memfun_validate = requires(T t) {
        t.validate();
    };

    we can use concept has_memfun_validate inside the function template together with 
    constexpr if and call validate on T only, if the method exists.


1.12.2 Conditional copy operations

    A wrapper<T> should behave like T.
    The wrapper shall have a copy constructor if T is copy constructible,
    and that it should have a trivial destructor if T is trivially destructible.

    Let's try to implement first requirement in C++17

    For the constrained copy constructor, we need to apply an enable_if and check whether 
    T is copy constructible and whether the parameter passed to the copy constructor is of type optional.

    This implementation is wrong because
    A copy constructor is never a template. It follows exactly the syntax T(const T&), that’s it. 
    We created a conversion constructor.

    The correct way to implement this in C++17, and before, was to derive from 
    either a class with a deleted copy constructor and copy optional assignment operator 
    or  derived from one with both defaulted.


    Implemetation in C++20

    In C++20, we can just write a copy constructor, as we always do. 
    No template is required. The class itself is already a template. 
    But we can apply the trailing requires to even non-templated methods. 
    This helps us because a trailing requires-clause doesn’t make the copy constructor anything else.

1.12.3 Conditional destructor

    To be as efficient as possible, a destructor should only be present if the type is non-trivially destructible. 
    Otherwise, the destructor should be defaulted, keeping this optional instance trivially destructible.

    The compiler does not allow us to create a templated destructor in the first place. 
    This saves us from making a mistake like before, where we failed to disable the copy constructor by making it a template.

    C++20
    we can put the trailing requires-clause on a destructor as well.

    Here, if the wrapped type is trivially destructible, the destructor should be defaulted, 
    but in case T is not trivially destructible, we need a destructor that calls the destructor of T for the optional internal storage.

1.12.4 Conditional methods

    What we have seen so far for the copy operations and the destructor works for all methods, including special members

**********/

#include <iostream>
#include <string>

// 1.12.1 Call method based in requires
template<typename T>
concept implements_display = requires(T t) {
    t.display();
};

struct Person {
    uint    age;
    std::string name;
    std::string addr;

    friend std::ostream& operator<<(std::ostream & os, const Person & p);
};

std::ostream& operator<<(std::ostream & os, const Person & p) {
    os << "Name " << p.name << ", Age " << p.age << ", Addr " << p.addr;
    return os;
}

struct Student : Person {
    std::string subj;

    void display() {
        std::cout << "Name " << name << ", Age " << age << ", Addr " << addr << ", Subject " << subj << '\n';
    }
};

template<typename T>
void display(T t) {
    if constexpr(implements_display<T>) {
        t.display();
    }
    else {
        std::cout << t << '\n';
    }
}

// 1.12.2 Conditional copy operations
template<typename T>
union storage_t {
    using aligned_storage_t = std::aligned_storage_t<sizeof(T), alignof(T)>;
    aligned_storage_t data;
    
    storage_t() = default;
    T* as() { return reinterpret_cast<T*>(&data); }
    // use placement new to create an instance of T inside this union
};

template<typename T>
class my_wrapper {
    storage_t<T>    data;

    public:
    my_wrapper() = default;

    /*
    This implementation is wrong because
    A copy constructor is never a template. 
    It follows exactly the syntax T(const T&), that’s it. 
    We created a conversion constructor.    
    */
    template<
        typename U,
        typename = std::enable_if_t<std::is_same_v<U, my_wrapper> and std::is_copy_constructible_v<T>>
    >
    my_wrapper(const U & ) {}
};

struct Copyable { };

struct NonCopyable {
    NonCopyable() = default;

    NonCopyable(const NonCopyable &) = delete;
    NonCopyable & operator=(const NonCopyable &) = delete;
};

template<typename T>
class my_wrapper_correct : std::conditional_t<std::is_copy_constructible_v<T>, Copyable, NonCopyable>
{

};

/*
template<typename T>
class my_wrapper_cpp20
{
    public:
    my_wrapper_cpp20() = default;

    my_wrapper_cpp20(const my_wrapper_cpp20 & )  
    requires std::is_copy_constructible_v<T>
    {

    }

};
*/

// 1.12.3 Conditional destructor
struct S {
    ~S() { std::cout << "~S\n"; }
    S() { std::cout << "S\n"; }
};

template<typename T>
class my_wrapper_cpp20
{
    storage_t<T>    data;
    bool            has_value{false};
    public:
    my_wrapper_cpp20() = default;

    my_wrapper_cpp20(const my_wrapper_cpp20 & )  
    requires std::is_copy_constructible_v<T>
    {

    }

    ~my_wrapper_cpp20() requires(not std::is_trivially_destructible_v<T>) {
        if(has_value) { 
            data.as()->~T();
            std::cout << "non trivial destructor\n";
        }
    }

    ~my_wrapper_cpp20() = default;

};

int main() {

    {
        // 1.12.1 Call method based in requires

        Student st1{{12, "Student-1", "Addr-1"}, "Math"};
        display(st1);

        Person p{30, "Person-2", "Addr-2"};
        display(p);
    }

    {
        // 1.12.2 Conditional copy operations

        {
            my_wrapper<Copyable> c1{};
            my_wrapper<Copyable> c2(c1);

            my_wrapper<NonCopyable> nc1;
            my_wrapper<NonCopyable> nc2(nc1);   // This is wrong
        }    

        {
            my_wrapper_correct<Copyable> c1{};
            my_wrapper_correct<Copyable> c2(c1);

            my_wrapper_correct<NonCopyable> nc1;
            // error: call to implicitly-deleted copy constructor of 'my_wrapper_correct<NonCopyable>'
            //my_wrapper_correct<NonCopyable> nc2(nc1);
        }   

        {
            my_wrapper_cpp20<Copyable> c1{};
            my_wrapper_cpp20<Copyable> c2(c1);

            my_wrapper_cpp20<NonCopyable> nc1;

            /*
            error: no matching constructor for initialization of 'my_wrapper_cpp20<NonCopyable>'
            note: candidate constructor not viable: constraints not satisfied
            because 'std::is_copy_constructible_v<NonCopyable>' evaluated to false
            */
            // my_wrapper_cpp20<NonCopyable> nc2(nc1);


            static_assert(not std::is_copy_constructible_v<NonCopyable>);
            static_assert(not std::is_copy_constructible_v<my_wrapper_cpp20<NonCopyable>>);

            static_assert(std::is_copy_constructible_v<Copyable>);
            static_assert(std::is_copy_constructible_v<my_wrapper_cpp20<Copyable>>);

        }  

    }

    {
        // 1.12.3 Conditional destructor
        {
            my_wrapper_cpp20<Copyable> c1{};
            my_wrapper_cpp20<Copyable> c2(c1);

            my_wrapper_cpp20<NonCopyable> nc1;

            /*
            error: no matching constructor for initialization of 'my_wrapper_cpp20<NonCopyable>'
            note: candidate constructor not viable: constraints not satisfied
            because 'std::is_copy_constructible_v<NonCopyable>' evaluated to false
            */
            // my_wrapper_cpp20<NonCopyable> nc2(nc1);
        } 

        {
            my_wrapper_cpp20<S> s;

            static_assert(not std::is_trivially_destructible_v<S>);
            static_assert(not std::is_trivially_destructible_v<my_wrapper_cpp20<S>>);

            static_assert(std::is_trivially_destructible_v<Copyable>);
            static_assert(std::is_trivially_destructible_v<my_wrapper_cpp20<Copyable>>);
        }
    }

    return 0; 
}

/*****
    END OF FILE
**********/


