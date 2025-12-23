/*****

References

    Programming with C++20 | Andreas Fertig
    https://en.cppreference.com/w/cpp/language/attributes/likely.html
    https://en.cppreference.com/w/cpp/language/attributes/no_unique_address.html

Chapter 11 | Language Updates

11.2 New Attributes

11.2.1 likely / unlikely

    These attributes may be applied to labels and statements (other than declaration-statements).
    They may not be simultaneously applied to the same label or statement.

    [[likely]] (or [[unlikely]]) Applies to a statement to allow the compiler to 
    optimize for the case where paths of execution including that statement are 
    more likely (or less likely) than any alternative path of execution that 
    does not include such a statement.

11.2.2 no_unique_address
    Applies to the name being declared in the declaration of a non-static data member that is not a bit-field.

    Makes this member subobject potentially-overlapping, i.e., 
    allows this member to be overlapped with other non-static data members 
    or base class subobjects of its class. 
    This means that if the member has an empty class type (e.g. stateless allocator), 
    the compiler may optimize it to occupy no space, just like if it were an empty base. 
    If the member is not empty, any tail padding in it may be also reused to store other data members.


**********/

#include <format>
#include <iostream>

int main() {

    {
        std::cout << std::format("=== {} ===\n", "11.2.1 likely / unlikely");
        const int val{1};
        switch(val) {
            case 0:
                std::cout << std::format("failure\n"); break;
            case 1:
                std::cout << std::format("success\n"); break;
            case 3:
                std::cout << std::format("out of resource\n"); break;
        }

    }

    {
        std::cout << std::format("=== {} ===\n", "11.2.2 no_unique_address");

        struct NonCopyable {
            NonCopyable()                       = default;
            NonCopyable(const NonCopyable &)    = delete;
            NonCopyable(NonCopyable &&)         = default; 
        };

        {
            struct Data {
                int data;
                NonCopyable nc;
            };

            Data d1{4};
            //Data d2{d1};

            std::cout << std::format("size without no_unique_address {}\n", sizeof(Data));
        }

        {
            struct Data {
                int data;
                [[no_unique_address]] NonCopyable nc;
            };

            Data d1{4};
            //Data d2{d1};

            std::cout << std::format("size with no_unique_address {}\n", sizeof(Data));
        }

    }

    return 0; 
}

/*****
    END OF FILE
**********/
