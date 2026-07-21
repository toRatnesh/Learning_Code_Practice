/*****

References

	episode https://www.youtube.com/watch?v=qcWC2yF0L7c

    code https://godbolt.org/z/hKaY15zbY

    To better handle fallthrough we can use following ways:

    1.  use break;
    2.  use [[fallthrough]] when its intended
    3.  treat switches as expressions, not statements, make all cases return statements
    4.  avoid 'default' if the rest is an expression
        the final path through the code should just return or error

**********/

#include <iostream> 
#include <exception>

enum class Color {
    RED,
    GREEN,
    BLACK
};

std::string to_string(const Color value) {

    switch(value) {
        case Color::RED:
            return "RED";
        case Color::GREEN:
            return "GREEN";
        case Color::BLACK:
            return "BLACK";
    }

    return "";
}

void useBreak(const Color value) {

    switch (value) {
        case Color::RED:
            std::cout << "Color RED\n";
            break;
        case Color::GREEN:
            std::cout << "Color GREEN\n";
            //break;    // warning: this statement may fall through [-Wimplicit-fallthrough=]
        case Color::BLACK:
            std::cout << "Color BLACK\n";
            break;
        default:
            std::cout << "Color " << to_string(value) << '\n';
    }
}

void useFallthrough(const Color value) {

    switch (value) {
        case Color::RED:
            std::cout << "Color RED\n";
            break;
        case Color::GREEN:
            std::cout << "Color GREEN\n";
            //[[fallthrough]];  // warning: this statement may fall through [-Wimplicit-fallthrough=]
        case Color::BLACK:
            std::cout << "Color BLACK\n";
            break;
        default:
            std::cout << "Color " << to_string(value) << '\n';
    }
}

void useExpression(const Color value) {
    
    auto display = [](const Color value) {
        std::cout << "Color " << to_string(value)  << '\n'; 
    };
    
    switch (value) {
        case Color::RED:
            return display(value);
        case Color::GREEN:
            return display(value);
        case Color::BLACK:
            return display(value);
    }

    throw std::runtime_error("value not in range");
}

int main() {

    {
        constexpr Color value{Color::RED};
        useBreak(value);
        useFallthrough(value);
        useExpression(value);
    }
    std::cout << '\n';

    {
        constexpr Color value{Color::GREEN};
        useBreak(value);
        useFallthrough(value);
        useExpression(value);
    }
    std::cout << '\n';

    {
        constexpr Color value{Color::BLACK};
        useBreak(value);
        useFallthrough(value);
        useExpression(value);
    }

    return 0;
}

/*****
    END OF FILE
**********/

