/*****

References

    episode https://www.youtube.com/watch?v=Rq4apPjnrsU
    https://en.cppreference.com/w/cpp/utility/format.html
    https://www.cppstories.com/2022/custom-stdformat-cpp20/

    custom fomatters are easy while custom format strings are harder

**********/

#include <iostream>
#include <format>
#include <string>

struct Student {
    std::string name;
    std::string id;
};


template<>
struct std::formatter<Student> {
    constexpr auto parse(std::format_parse_context & ctx) {
        return ctx.begin();
    }

    auto format(const Student & st, std::format_context & ctx) const  {
        return std::format_to(ctx.out(), "Student name: {}, id: {}", st.name, st.id);
    }
};


int main() {

    Student st{"Student-1", "Student-1-Id-1"};
    std::cout << std::format("{}\n", st);

    return 0;
}

/*****
    END OF FILE
**********/
