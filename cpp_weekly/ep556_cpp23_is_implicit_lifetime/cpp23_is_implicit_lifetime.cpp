/*****

References:
    episode     https://www.youtube.com/watch?v=kJ9dJfuUCHg
    https://en.cppreference.com/cpp/types/is_implicit_lifetime
    Code        https://godbolt.org/z/WPa8c3W5h

    template< class T >
    struct is_implicit_lifetime;        // (since C++23)

    std::is_implicit_lifetime is a UnaryTypeTrait.

    If T is an implicit-lifetime type, provides the member constant value equal to true.
    For any other type, value is false.

    The behavior is undefined if T is an incomplete type 
    other than an array type or (possibly cv-qualified) void.

    If the program adds specializations for std::is_implicit_lifetime 
    or std::is_implicit_lifetime_v, the behavior is undefined.

    Implicit lifetime starts only once

**********/

#include <iostream>
#include <type_traits>
#include <string>
#include <print>

struct SAggregate {
    int     ival;
    float   fval;
};

class CAggregate {
    public:

    int     ival;
    float   fval;
};

class DefaultConstructor {
    int x{};
    public:
    DefaultConstructor() = default;
};

class DefaultDestructor {
    int x{};
    public:
    ~DefaultDestructor() = default;
};

struct UserConstructor {
    int x{};
    UserConstructor();
};
UserConstructor::UserConstructor() = default;

struct UserDestructor {
    int x{};
    ~UserDestructor();
};
UserDestructor::~UserDestructor() = default;

int main()
{
    static_assert(std::is_implicit_lifetime_v<bool>);
    static_assert(std::is_implicit_lifetime_v<char>);
    static_assert(std::is_implicit_lifetime_v<int>);
    static_assert(std::is_implicit_lifetime_v<double>);    
    std::println("std::is_implicit_lifetime_v<bool> {}", std::is_implicit_lifetime_v<bool> );
    std::println("std::is_implicit_lifetime_v<char> {}", std::is_implicit_lifetime_v<char> );
    std::println("std::is_implicit_lifetime_v<int> {}", std::is_implicit_lifetime_v<int> );
    std::println("std::is_implicit_lifetime_v<double> {}", std::is_implicit_lifetime_v<double> );
    std::println();

    static_assert(std::is_implicit_lifetime_v<const int>);
    static_assert(std::is_implicit_lifetime_v<volatile int>);
    std::println("std::is_implicit_lifetime_v<const int> {}", std::is_implicit_lifetime_v<const int> );
    std::println("std::is_implicit_lifetime_v<volatile int> {}", std::is_implicit_lifetime_v<volatile int> );
    std::println();

    static_assert(std::is_implicit_lifetime_v<int *>);
    static_assert(std::is_implicit_lifetime_v<void *>);
    std::println("std::is_implicit_lifetime_v<int *> {}", std::is_implicit_lifetime_v<int *> );
    std::println("std::is_implicit_lifetime_v<void *> {}", std::is_implicit_lifetime_v<void *> );
    std::println();

    static_assert(not std::is_implicit_lifetime_v<std::string>);
    std::println("std::is_implicit_lifetime_v<std::string> {}", std::is_implicit_lifetime_v<std::string>);
    std::println();

    static_assert(std::is_implicit_lifetime_v<SAggregate>);
    static_assert(std::is_implicit_lifetime_v<CAggregate>);
    std::println("std::is_implicit_lifetime_v<SAggregate> {}", std::is_implicit_lifetime_v<SAggregate>);
    std::println("std::is_implicit_lifetime_v<CAggregate> {}", std::is_implicit_lifetime_v<CAggregate>);
    std::println();

    static_assert(std::is_implicit_lifetime_v<DefaultConstructor>);
    static_assert(std::is_implicit_lifetime_v<DefaultDestructor>);
    std::println("std::is_implicit_lifetime_v<DefaultConstructor> {}", std::is_implicit_lifetime_v<DefaultConstructor>);
    std::println("std::is_implicit_lifetime_v<DefaultDestructor> {}", std::is_implicit_lifetime_v<DefaultDestructor>);
    std::println();

    static_assert(std::is_implicit_lifetime_v<UserConstructor>);
    static_assert(not std::is_implicit_lifetime_v<UserDestructor>);
    std::println("std::is_implicit_lifetime_v<UserConstructor> {}", std::is_implicit_lifetime_v<UserConstructor>);
    std::println("std::is_implicit_lifetime_v<UserDestructor> {}", std::is_implicit_lifetime_v<UserDestructor>);
    std::println();


    {
        UserConstructor * pdata = reinterpret_cast<UserConstructor*>(std::malloc(sizeof(UserConstructor)));
        pdata->x = 5;    // OK object lifetime started implicitly at time of allocation
        std::println("val {}", pdata->x);
        std::free(pdata);
    }

    {
        UserDestructor * pdata = reinterpret_cast<UserDestructor*>(std::malloc(sizeof(UserDestructor)));
        pdata->x = 5;    // UB, object lifetime not started yet
        std::println("val {}", pdata->x);
        std::free(pdata);
    }

    {
        UserDestructor * pdata = reinterpret_cast<UserDestructor*>(std::malloc(sizeof(UserDestructor)));
        
        std::construct_at(pdata , 5);
        pdata->x = 15;    // OK, object lifetime started
        std::println("val {}", pdata->x);
        
        std::destroy_at(pdata);
        std::free(pdata);
    }

    return 0;
}

/*****
    END OF FILE
**********/


