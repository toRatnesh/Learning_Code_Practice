
/*****

This example demonstrates about confusing interface of reset 
In case a owner class and the object class has same interface with name reset

**********/

#include <iostream>
#include <memory>
#include <any>
#include <string>

int main() {

    auto up_val = std::make_unique<std::any>(std::string("unique pointer to any"));
    if(up_val) {
        if(up_val->has_value()) {
            std::cout << std::any_cast<std::string>(*up_val) << '\n';
        } else {
            std::cout << "std::any does not contains an obect\n";
        }
    } else {
        std::cout << "Unique pointer does not owns an obect\n";
    }
    
    up_val->reset();            // reset any object (* and -> provide access to the object owned)
    if(up_val) {
        if(up_val->has_value()) {
            std::cout << std::any_cast<std::string>(*up_val) << '\n';
        } else {
            std::cout << "std::any does not contains an obect\n";
        }
    } else {
        std::cout << "Unique pointer does not owns an obect\n";
    }

    (*up_val).emplace<std::string>("setting another string to any");
    if(up_val) {
        if(up_val->has_value()) {
            std::cout << std::any_cast<std::string>(*up_val) << '\n';
        } else {
            std::cout << "std::any does not contains an obect\n";
        }
    } else {
        std::cout << "Unique pointer does not owns an obect\n";
    }

    up_val.reset();            // reset unique+ptr
    if(up_val) {
        if(up_val->has_value()) {
            std::cout << std::any_cast<std::string>(*up_val) << '\n';
        } else {
            std::cout << "std::any does not contains an obect\n";
        }
    } else {
        std::cout << "Unique pointer does not owns an obect\n";
    }

    return 0;
}

/*****
    END OF FILE
**********/


