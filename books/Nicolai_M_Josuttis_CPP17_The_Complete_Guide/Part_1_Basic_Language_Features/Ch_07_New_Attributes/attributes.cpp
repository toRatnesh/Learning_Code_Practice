/************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

Attributes
        attributes (formal annotations that enable or disable warnings)

[[nodiscard]]
    used to show warnings by compiler if return value of a function is not used
    used to indicates possible issue when return value is not used
        memory leaks, unexpected or non-intuitive behavior, unnecessary overhead

[[maybe_unused]]
	used to avoid warnings by the compiler for not using a name or entity
	ay be applied to the 
	declaration of a class, 
	a type definition with typedef or using,
	a variable, 
	a non-static data member, 
	a function, 
	an enumeration type, or 
	an enumerator (enumeration value)
	
	NOTE;
	can’t apply [[maybe_unused]] to a statement, so, you cannot counter [[nodiscard]] with [[maybe_unused]]

[[fallthrough]]
	used to avoid warnings by the compiler for not having a break statement after a sequence of one or more case labels inside a switch statement
	
General Attribute Extensions
	1. Attributes are now allowed to mark namespaces, also possible for inline and unnamed namespaces
	2. Attributes are now allowed to mark enumerators. 
		NOTE: for enumerators the attribute is placed behind the identifier
	3. For user-defined attributes, you can now use a using prefix to avoid the repetition of the attribute namespace for each attribute
		[[MyLib::WebService, MyLib::RestService, MyLib::doc("html")]]	void foo();
		[[using MyLib: WebService, RestService, doc("html")]]			void foo();

*************/

#include <iostream>

[[nodiscard]] int can_not_ignore_return_value() {
    return 5;
}

void learn_fallthrough(const int val) {
    switch(val) {
        case 1:
            std::puts("this will generate warning because break is not used"); // warning: this statement may fall through
        case 2:
            std::puts("this will not generate warning because [[fallthrough]] used");
            [[fallthrough]];
        case 3:
            std::puts("this will not generate warning because break is used");
            break;
        default:
            std::puts("default");
    }
}

enum class Color {
    RED,
    GREEN,
    BLUE, 
    BLACK [[deprecated]] = BLUE
};
void foo([[maybe_unused]] Color color) { }

namespace [[deprecated]] nonstd {
    void foo() { }
}



int main() {
    std::puts("=== [[nodiscard]] ===");
    can_not_ignore_return_value(); // warning: ignoring return value of 'int can_not_ignore_return_value()', declared with attribute 'nodiscard' [-Wunused-result]
    
    std::puts("=== [[maybe_unused]] ===");
    [[maybe_unused]] can_not_ignore_return_value(); // warning: ignoring return value of 'int can_not_ignore_return_value()', declared with attribute 'nodiscard' [-Wunused-result]
    [[maybe_unused]] int val = can_not_ignore_return_value();

    std::puts("=== [[fallthrough]] ===");
    learn_fallthrough(2);

    std::puts("=== [[deprecated]] ===");
    nonstd::foo(); // warning: 'nonstd' is deprecated [-Wdeprecated-declarations]

    foo(Color::RED);
    foo(Color::BLUE);
    foo(Color::BLACK); // warning: 'Color::BLACK' is deprecated [-Wdeprecated-declarations]

    return 0;
}

/************
    END OF FILE
*************/
