/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html#Designated_initializers
    https://en.cppreference.com/w/cpp/language/list_initialization.html

Chapter 8 | Aggregates: Designated initializers and more

8.2 Designated initializers

8.2.1 Designated initializers in C

    C has designated initializers for structs
    in example
    const Point3d p1{.x = 3.5, .y = 4.3, .z = 6};
    .x = 3.5 is called a designated initializer

8.2.2 Designated initializers in C++20

    since C++20, C++ supports designated initializers

    Differences from C++ in C:
    1.  if we opt-in, all values we provide must use the designated initializer syntax
    2.  The designated initializers must appear in the declaration order of the data members. 
        The compiler evaluates them from left to right
    3.  Designators must be unique, In C you can list the same designator multiple times
    4.  C++ allows brace-or-equal initialization, C allows only equal initialization
    5.  to nest designators, we need equal-or-brace initialization

    Benefit of brace initialization:
    .   prevents narrowing conversions at compile-time
    .   always performs a default or zero initialization
    .   it prevents the most vertexing parse problem

    designated initializers for array elements works in C but not in C++

8.2.3 Initializing a subset of an aggregate with designated initializers

    if we initialize a subset of an aggregate using designated initializers rest of the aggregate members are default initialized

8.2.4 Initialize a subset with designated initializers without in-class member initializers

    braced initialization ensures, that all unnamed members are initialized with default or zero initialization
    we can use designated initializers to directly return an aggregate value to take benefits of RVO

8.2.5 Named arguments in C++: Aggregates with designated initializers

    For a large number of parameters, aggregates with designated initializers are a good option

8.2.6 Overload resolution and designated initializers

    during overload resolution, the order of the designators doesn’t matter
    if we are able to distinguish which type is meant by looking at the initialization, the compiler is as well

**********/

#include <iostream>
#include <format>
#include <string>
#include <cstdint>
#include <type_traits>

struct Student {
    std::string     name;
    uint32_t         age = 10;
    double          cgpa;
};

template<>
struct std::formatter<Student> {

    constexpr auto parse(std::format_parse_context & ctx) {
        return ctx.begin();
    }

    auto format(const Student & st, std::format_context & ctx) const {
        return std::format_to(ctx.out(), "Student name {:10} age {:2} CGPA {:3}", st.name, st.age, st.cgpa);
    }
};

struct RaiseAlarmData {
    std::string name;
    std::string severity;
    std::string cause;
    std::string remedy;
};

void raiseAlarm(const RaiseAlarmData & alarm_data) {
    std::cout << std::format("Raising alarm name: {}, severity: {}, cause: {}, remedy: {}\n", 
        alarm_data.name, alarm_data.severity, alarm_data.cause, alarm_data.remedy);
}

struct Point {
    int x;
    int y;
    int z;
};

struct Point2 {
    int z;
    int y;
    int X;
};

void display(const Point & p) {  
    std::cout << std::format("Point {} {} {}\n", p.x, p.y, p.z);
};
void display(const Point2 & p) {  
    std::cout << std::format("Point2 {} {} {}\n", p.X, p.y, p.z);
};


int main() {

    {
        std::cout << R"(=== 8.2.1 Designated initializers in C ===)" << '\n';

        struct Point3d {
            double x;
            double y;
            double z;
        };

        [[maybe_unused]] const Point3d p1{.x = 3.5, .y = 4.3, .z = 6};

        std::cout << std::format("Point {{ {}, {}, {} }}\n", p1.x, p1.y, p1.z);
    }

    {
        std::cout << R"(=== 8.2.2 Designated initializers in C++20 ===)" << '\n';

        {
            const Student st{"Student-1", 5, 3.4};
            std::cout << std::format("{}\n", st);
        }

        {
            // error: type 'double' cannot be narrowed to 'uint32_t' (aka 'unsigned int') in initializer list
            //const Student st{.name{"Student-1"}, .age{5.2}, .cgpa{3.4}};
            //std::cout << std::format("{}\n", st);
        }


        // if we opt-in, all values we provide must use the designated initializer syntax
        {
            const Student st{.name = "Student-1", .age = 2, .cgpa = 3.4};
            std::cout << std::format("{}\n", st);
        }

        {
            // The designated initializers must appear in the declaration order of the data members. 
            
            // CE error: designator order for field 'Student::age' does not match declaration order in 'const Student'
            // NOTE: clang works fine
            //const Student st{.name = "Student-1", .cgpa = 3.4, .age = 12};
            //std::cout << std::format("{}\n", st);
        }

        {
            // Designators must be unique, In C you can list the same designator multiple times

            // CE error: '.age' designator used multiple times in the same initializer list
            // NOTE: clang works fine
            //const Student st{.name = "Student-1", .age = 7, .age = 6, .cgpa = 3.4};
            //std::cout << std::format("{}\n", st);
        }

        {
            // C++ allows brace-or-equal initialization, C allows only equal initialization

            {
                const Student st{.name = "Student-1", .age = 2, .cgpa = 3.4};
                std::cout << std::format("{}\n", st);
            }  

            {
                const Student st{.name{"Student-1"}, .age{14}, .cgpa{3.4}};
                std::cout << std::format("{}\n", st);
            }

        }

        {
            // to nest designators, we need equal-or-brace initialization

            struct Group {
                std::string group;
                Student     st;
            };

            {
            Group g{ .group{"Group-1"}, .st{.name{"Student-1"}, .age{14}, .cgpa{3.4}} };
            std::cout << std::format("{} {}\n", g.group, g.st);                
            }

            {
            Group g{ .group = "Group-1", .st{.name{"Student-1"}, .age = 14, .cgpa{3.4}} };
            std::cout << std::format("{} {}\n", g.group, g.st);                
            }            
        }

        {
            const Student st{.name = "Student-1", .cgpa = 3.4}; // age is default initialized
            std::cout << std::format("{}\n", st);
        }

    }

    {
        std::cout << R"(=== 8.2.3 Initializing a subset of an aggregate with designated initializers ===)" << '\n';

        const Student st{.name = "Student-1", .cgpa = 3.4}; // age is default initialized
        std::cout << std::format("{}\n", st);

    }
    
    {
        std::cout << R"(=== 8.2.4 Initialize a subset with designated initializers without in-class member initializers ===)" << '\n';
        const Student st{.name = "Student-1", .age = 11}; 
        std::cout << std::format("{}\n", st);
    }
    
    {
        std::cout << R"(=== 8.2.5 Named arguments in C++: Aggregates with designated initializers ===)" << '\n';
        raiseAlarm({.name = "Server storage", .severity="major", .cause="storage is 75% full", .remedy="clean up temporary data"});
    }

    {
        std::cout << R"(=== 8.2.6 Overload resolution and designated initializers ===)" << '\n';

        display({.X{2}});
        
        //display({.y{2}});   // CE error: call of overloaded 'display(<brace-enclosed initializer list>)' is ambiguous


    }

    return 0;
}

/*****
    END OF FILE
**********/

