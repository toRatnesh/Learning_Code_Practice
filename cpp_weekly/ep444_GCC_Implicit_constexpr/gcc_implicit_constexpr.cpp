/*****

ep444_GCC_Implicit_constexpr

References
    episode https://www.youtube.com/watch?v=CHc39_qCgMU

-fimplicit-constexpr
    Make inline functions implicitly constexpr, if they satisfy the requirements for a constexpr function.
    This option can be used in C++14 mode or later. 
    This can result in initialization changing from dynamic to static and other optimizations.

**********/

//constexpr auto get_value() { return 14; }
//auto get_value() { return 14; }
inline auto get_value() { return 14; }

int main() {

    const auto val = get_value();
    const auto mul = 5;

    auto lambda = [](){
        return (val * mul) + 5;
    };

    static_assert(lambda() == 75);

    return 0;
}

/*****
    END OF FILE
**********/

