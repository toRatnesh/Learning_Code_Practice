/*****

ep443_Stupid_constexpr_Tricks

References
    episode https://www.youtube.com/watch?v=HNn-PmrL5X8

**********/

constexpr auto get_value() {
    return 23;
}

int main() {
    // const integral initialized by a constant expression is itself constant expression
    const auto val = get_value();
    const auto mul = 10;

    // no need to capture constexpr val and mul
    // lambda is implicitly constexpr
    const auto res = [](){
        return (val * mul) + 5;
    }();

    static_assert(235 == res);

    return 0;
}

/*****
    END OF FILE
**********/

