/*******

References
    C++17 - The Complete Guide | Nicolai M. Josuttis
	https://en.cppreference.com/w/cpp/string/basic_string_view


19 String Views

std::string_view objects refer to external character sequences without owning them.
The object can be considered as a reference to a character sequence.
It is also potentially dangerous, because similar to raw pointers it is up to the programmer to ensure that the referred character sequences is still valid

19.1 Differences to std::string

In contrast to std::string, std::string_view objects have the following properties:

The underlying character sequences are read-only. You can only assign a new value, swap values, and remove characters at the beginning or the end.
The character sequences are not guaranteed to be null terminated.
The value can be the nullptr
There is no allocator support

use size() before accessing characters via operator[] or data()

******************/

#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::string         astr{"sample string"};
    std::string_view    asview{"sample string view"};

    std::clog << "A string: " << astr << ", size: " << astr.size() << '\n';
    std::clog << "A string view: " << asview << ", size: " << asview.size() << '\n';

    // underlying character sequences are read-only
    astr[0] = 'S';
    //asview[0] = 'S'; // CE error: assignment of read-only location 'asview.std::basic_string_view<char>::operator[](0)'

    // character sequences are not guaranteed to be null terminated.
    std::clog << R"(astr[astr.size()]: )" <<  astr[astr.size()] << '\n';
    // accessing asview[asview.size()] is undefined behavior because it is not guaranteed to be '\0'
    std::clog << R"(asview[asview.size()]: )" << asview[asview.size()] << '\n'; 

    std::string         def_astr;
    std::string_view    def_asview;


    std::clog << "Default string size: " << def_astr.size() << '\n';
    std::clog << "Default string view size: " << def_asview.size() << '\n';
    
    std::clog << "Default string data: " << *def_astr.data() << '\n';
    //std::clog << "Default string view data: " << *def_asview.data() << '\n'; // RUNTIME ERROR

    return 0;
}

/*****
    END OF FILE
********/

