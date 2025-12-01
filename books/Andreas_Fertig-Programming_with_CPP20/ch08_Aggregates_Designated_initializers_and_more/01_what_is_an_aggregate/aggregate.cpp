/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html#Designated_initializers
    https://en.cppreference.com/w/cpp/language/list_initialization.html

Chapter 8 | Aggregates: Designated initializers and more

8.1 What is an aggregate

An aggregate is one of the following types:

    ->  array types
    ->  class types that has
        .   no user-declared constructors                           (until C++11)
        .   no user-provided, inherited, or explicit constructors   (since C++11)
                                                                    (until C++20)
        .   no user-declared or inherited constructors              (since C++20)

        .   no private or protected direct non-static data members

        .   no base classes                                         (until C++17)
        .   no virtual base classes                                 (since C++17)
        .   no private or protected direct base classes             (since C++17)

        .   no virtual member functions

        .   no default member initializers                          (since C++11)
                                                                    (until C++14)


**********/

#include <format>
#include <iostream>
#include <string>

int main() {
    {
        struct Data {
            int i;
            double d;
        };

        std::cout << R"(1 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Data {
            int i;
            double d;
            std::string s;
        };
        
        std::cout << R"(2 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Data {
            int i;
            double d;
            std::string s;

            Data() = default;
        };

        // THIS IS AN AGGREGATE SINCE C++ 11 UNTIL C++20
        std::cout << R"(3 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Data {
            int i;
            double d;
            std::string s;

            Data(const int i, const double d, const std::string s)
                : i{i}, d{d}, s{s} {}
        };

        std::cout << R"(4 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Data {
            int i;
            double d;
            std::string s;

            explicit Data(const int i)
                : i{i} {}
        };

        std::cout << R"(5 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Data {
            int i;
            double d;

            explicit Data(const int i) : i{i}, d{0} { }
        };

        std::cout << R"(6 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }


    {
        struct Base {
            int bi;
        };

        struct Data : public Base {
            int i;
            double d;
            std::string s;
        };

        std::cout << R"(7 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    {
        struct Base {
            int bi = 1;
        };

        struct Data : public Base {
            int i = 2;
            double d = 3.4;
            std::string s{"C++ 14 Aggregate member initialization"};
        };

        std::cout << R"(8 - std::is_aggregate_v<Data> )" << std::boolalpha << std::is_aggregate_v<Data> << '\n';
    }

    return 0;
}

/*****
    END OF FILE
**********/
