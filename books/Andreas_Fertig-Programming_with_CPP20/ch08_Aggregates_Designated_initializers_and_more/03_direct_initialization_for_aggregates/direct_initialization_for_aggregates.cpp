/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html
    https://en.cppreference.com/w/cpp/language/aggregate_initialization.html#Designated_initializers
    https://en.cppreference.com/w/cpp/language/list_initialization.html

Chapter 8 | Aggregates: Designated initializers and more

8.3 Direct-initialization for aggregates

8.3.1 Initialization forms: Braced or parenthesis initialization

    Braced initialization:
        .   aka list initialization
        .   prevents narrowing conversion
        .   perform a default ot zero initialization
        .   if present, triggers a constructor, which takes a
std::initializer_list

    Parenthesis initialization:
        .   supported since C++20

        Limitations:
        .   narrow conversion are possible
        .   most vertexing parse issue still remains same
        .   can not use for nested aggregate initialization
        .   can not use designated initializer
        .   might cause dangling references for rvalue references


8.3.2 Aggregates with user-declared constructors

    a breaking change
    C++20, structs or classes, as well as unions,
    with user-declared constructors are no longer qualify as aggregates

    C++17, structs or classes, as well as unions,
    with user-declared constructors did classify as aggregates

    In C++17 braced initialization for aggregates can bypass the deleted constructor

    C++20 reduces the gap between parenthesis and braced initialization

**********/

#include <format>
#include <iostream>
#include <string>

struct Point2d {
    int x;
    int y;
};

struct Point3d {
    Point2d p;
    int z;
};

struct UseRvalue {
    int&& rval;
};

template <>
struct std::formatter<Point2d> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto format(const Point2d& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Point {{{}, {}}}", p.x, p.y);
    }
};

template <>
struct std::formatter<Point3d> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto format(const Point3d& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Point {{{}, {}, {}}}", p.p.x, p.p.y,
                              p.z);
    }
};

template <>
struct std::formatter<UseRvalue> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto format(const UseRvalue& val, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Rvalue {}", val.rval);
    }
};

int main() {
    {
        std::cout << std::format(
            "=== 8.3.1 Initialization forms: Braced or parenthesis "
            "initialization ===\n");

        {
            std::cout << std::format("=== Braced initialization ===\n");
            //{ Point2d p2{3, 4.2}; } // error: narrowing conversion of
            //'4.2000000000000002e+0' from 'double' to 'int'
            {
                Point2d p2{.x{3}, .y{4}};
                std::cout << std::format("{}\n", p2);
            }
            {
                Point3d p3{};
                std::cout << std::format("{}\n", p3);
            }
            {
                Point3d p3{.p{.x{3}, .y{4}}, .z{5}};
                std::cout << std::format("{}\n", p3);
            }
            {
                UseRvalue rval{9};
                std::cout << std::format("{}\n", rval);
            }
        }

        {
            std::cout << std::format("=== Parenthesis initialization ===\n");

            {
                Point2d p2(3, 4.2);
            }  // narrow conversion allowed

            {
                // can not use designated initializer
                // Point2d p2(.x{3}, .y{4});       // error: expected expression
            }
            {
                Point3d p3();  // most vertexing parse issue still remains same
                // std::cout << std::format("{}\n", p3);
            }
            {
                // can not use for nested aggregate initialization
                // Point3d p3((3, 4), 5);  // error: no viable conversion from
                // 'int' to 'Point2d'
            }
            {
                UseRvalue rval(9);  // might cause dangling references for rvalue references
                // std::cout << std::format("{}\n", rval); // Runtime error AddressSanitizer: stack-use-after-scope
            }
        }
    }

    {
        std::cout << std::format("=== 8.3.2 Aggregates with user-declared constructors === \n");
        struct Data {
            std::string id;
            int val;

            Data(const std::string) = delete;
        };

        {
            // valid in C++17
            //Data data{"id-1"};      // CE error: use of deleted function 'main()::Data::Data(std::string)'
        }

        {
            //Data data("id-1");  // CE error: use of deleted function 'main()::Data::Data(std::string)'
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/
