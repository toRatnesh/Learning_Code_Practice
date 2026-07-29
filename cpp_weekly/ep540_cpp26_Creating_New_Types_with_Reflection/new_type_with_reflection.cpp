/*****

References:
    episode     https://www.youtube.com/watch?v=ZBqTr6YRROA
    https://cppreference.com/cpp/meta/reflection

    code https://godbolt.org/z/n66doPqns

    This example demonstrates how to create a new type using C++ reflection

**********/

#include <print>
#include <meta>
#include <vector>

auto create_type_for_point2d() {
    
    struct point2d;

    consteval {
        std::vector<std::meta::info>    point2d_members = {
            std::meta::data_member_spec(^^int, {.name="x"}),
            std::meta::data_member_spec(^^int, {.name="y"})
        };

        std::meta::define_aggregate(^^point2d, point2d_members);
    }

    return point2d{};
}

using point2d_t = decltype(create_type_for_point2d());

int main()
{
    point2d_t p{.x=5, .y=7};

    std::println("Point {{{}, {}}}", p.x, p.y);

    return 0;
}

/*****
    END OF FILE
**********/

