/*****

References
    https://en.cppreference.com/w/cpp/language/copy_constructor
    https://www.youtube.com/watch?v=zG0X221arX8

copy constructor can not be a template function
if such a function is present it will act as a conversion function

copy constructor should either have no other parameters, or all other parameters should have default arguments

Syntax

class-name (parameter-list);                                    (1)	
class-name (parameter-list ) function-body                      (2)	
class-name (single-parameter-list) = default;                   (3)	(since C++11)
class-name (parameter-list) = delete;                           (4)	(since C++11)
class-name ::class-name (parameter-list) function-body	        (5)	
class-name ::class-name (single-parameter-list) = default;      (6)	(since C++11)

class-name      - the class whose copy constructor is being declared
parameter-list	- a non-empty parameter list satisfying all following conditions:
                    . given the class type as T, the first parameter is of type T&, const T&, volatile T& or const volatile T&, and
                    . either there are no other parameters, or all other parameters have default arguments.
single-parameter-list   - a parameter list of only one parameter, which is of type T&, const T&, volatile T& or const volatile T& and does not have a default argument
function-body   - the function body of the copy constructor

**********/

#include <iostream>

class ValidCopyCx {
   public:
    ValidCopyCx() { std::cout << "ValidCopyCx()\n"; }
    ValidCopyCx(const ValidCopyCx&) {
        std::cout << "ValidCopyCx(const ValidCopyCx & )\n";
    }
};

class AnotherValidCopyCx {
   public:
    AnotherValidCopyCx() { std::cout << "AnotherValidCopyCx()\n"; }
    AnotherValidCopyCx(const AnotherValidCopyCx &, 
                        int ival = 1, std::string sval = "sample-string") {
        std::cout << R"(AnotherValidCopyCx(const AnotherValidCopyCx &, int ival = 1, std::string sval = "sample-string"))" << '\n';
    }
};

class InvalidCopyCx {
   public:
    InvalidCopyCx() { std::cout << "InvalidCopyCx()\n"; }

    template <typename T>
    InvalidCopyCx(const T& t) {
        std::cout << "InvalidCopyCx(const T & t)\n";
    }
};

int main() {
    {
        ValidCopyCx vc1;
        ValidCopyCx vc2{vc1};
    }
    std::cout << '\n';
    {
        AnotherValidCopyCx avc1;
        AnotherValidCopyCx avc2{avc1};
    }
    std::cout << '\n';    
    {
        InvalidCopyCx icx1;
        InvalidCopyCx icx2{icx1};
    }

    return 0;
}

/*****
    END OF FILE
**********/

