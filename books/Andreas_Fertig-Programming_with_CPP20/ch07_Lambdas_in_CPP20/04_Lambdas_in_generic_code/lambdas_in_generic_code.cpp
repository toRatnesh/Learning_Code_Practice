/*****

References

    Programming with C++20 | Andreas Fertig


Chapter 7 | Lambdas in C++20: New features

    There are several changes therein to make lambdas even more powerful.

7.4 Lambdas in generic code

	Consider a book publisher also publish magazines and other material, all with an ISBN.
	
	With that additional type, a new use-case is to have a more generic map that works with Book and Magazine.
	
	Apart from changing the name of the type we also need to change the compare lambda.
	
	To make the previous version work(section 7.3), we can fall back to C++14’s generic lambdas. 
	By making the former Book parameters auto, the code compiles.

7.4.1 Lambdas with templated-head

	They are both auto and with that can be independent types.

	We can also decide to move away from the lambda and use a function-template instead.

	C++20 adds the ability to lambdas to have a template-head, like functions or methods.
	This enables us to provide not only type-parameters but also NTTP for a lambda.

	The syntax is the same as for other templates, except that we do not need to spell out the template.
	The template-head itself comes after the capture list

	In improved code for compare using template both parameters must be of the same type

7.4.2 Variadic lambda arguments

    Suppose we have a generic lambda that has a variadic number of arguments.
    This variadic generic lambda should now forward its arguments to another function.

    we can avoid some copies of strings or other resource-intensive objects when we forward them, saving additional allocations and copies.

7.4.3 Forwarding variadic lambda arguments

	auto stands for a template parameter.
	We can apply decltype on it to get back the type and supply this to std::forward.
	But it still is not as clean and simple as it should be.

	In C++20, all we have to do is to add the template-head and switch from auto as parameter type to the chosen Ts
	we would write a normal template, create a variadic pack called Ts and use this with std::forward
	No decltype necessary

**********/

#include <iostream>
#include <map>
#include <string>
#include <source_location>
#include <format>

struct Book {
    std::string m_title;
    std::string m_isbn;
};

struct Magazine {
    std::string m_title;
    std::string m_isbn;
};

struct Price {
    double m_price;
};

template <typename KEY>
using map_sorted_by_isbn_t = std::map<KEY, Price,
                                      decltype(

/*  This comparison has drawback that it can accept different parameters
                                          [](const auto& fe, const auto& se) {
                                              return fe.m_isbn > se.m_isbn;
                                          }
*/
                                          []<typename T>(const T& fe,
                                                         const T& se) {
                                              return fe.m_isbn > se.m_isbn;
                                          }

                                          )>;

void display(const auto& fa_map) {
    for (const auto& [k, v] : fa_map) {
        std::cout << k.m_title << ' ' << k.m_isbn << ',' << v.m_price << '\n';
    }
}

template<typename ...Args>
void logit(Args ... args) {
    ((std::cout << args << ' '), ...) << '\n';   
}

// 7.4.2 Variadic lambda arguments
auto loggerCpp17() {
    return [=](auto ...args) {
        logit(std::forward<decltype(args)>(args)...);
    };
}

// 7.4.3 Forwarding variadic lambda arguments

auto loggerCpp20() {
    return [=]<typename ...Args>(Args ...args) {
        logit(std::forward<Args>(args)...);
    };
}

auto LOG17 = loggerCpp17();
auto LOG20 = loggerCpp20();

int main() {
    std::cout << "=== 7.4.1 Lambdas with templated-head === \n";
    {
        std::cout << "--- Storing Book in map ---\n";
        map_sorted_by_isbn_t<Book> book_map{{{"Book-1", "2023-976"}, {789.45}},
                                            {{"Book-2", "2021-578"}, {356.28}},
                                            {{"Book-3", "2022-489"}, {287.37}}};

        display(book_map);
    }

    {
        std::cout << "--- Storing Magazine in map ---\n";
        map_sorted_by_isbn_t<Magazine> magazine_map{
            {{"Magazine-1", "2023-976"}, {789.45}},
            {{"Magazine-2", "2021-578"}, {356.28}},
            {{"Magazine-3", "2022-489"}, {287.37}}};

        display(magazine_map);
    }

    
    {   std::cout << "\n=== 7.4.2 Variadic lambda arguments ===\n";
    
        LOG17("This is a sample log");
        LOG17("This is also a log");
        LOG17("Logging an int value", 598);
        LOG17(234, 56.98);
    }

    
    {   std::cout << "\n=== 7.4.3 Forwarding variadic lambda arguments === \n";

        LOG20("This is a sample log");
        LOG20("This is also a log");
        LOG20("Logging an int value", 598);
        LOG20(234, 56.98);
    }
    return 0;
}

/*****
    END OF FILE
**********/

