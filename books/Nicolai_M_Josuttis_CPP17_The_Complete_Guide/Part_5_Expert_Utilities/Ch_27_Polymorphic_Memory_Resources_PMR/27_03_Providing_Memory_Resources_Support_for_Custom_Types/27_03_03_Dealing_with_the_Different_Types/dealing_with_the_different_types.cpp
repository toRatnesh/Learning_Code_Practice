/**********

References

    C++17 - The Complete Guide | Nicolai M. Josuttis
    https://en.cppreference.com/w/cpp/header/memory_resource
    https://en.cppreference.com/w/cpp/memory/polymorphic_allocator

27.3 Providing Memory Resources Support for Custom Types

27.3.3 Dealing with the Different Types

    There is an explicit but no implicit conversion between different string types.
    The explicit conversion is supported, because any string implicitly converts to a std::string_view, which has an explicit conversion to any string type. The further is cheap, but the latter needs to allocate memory.
    We might want to provide additional constructors, but the good thing with not providing them is that programmers are forced to implement the expensive conversion.

*************/

#include <iostream>
#include <memory_resource>
#include <array>
#include <vector>
#include <cstddef>

namespace nonstd {

    class Student {
        std::pmr::string        m_name;
        public:
        using allocator_type = std::pmr::polymorphic_allocator<std::byte>;
        Student(std::pmr::string name, allocator_type alloc = {}) 
            : m_name{std::move(name), alloc} {
                std::cout << "Construtor - Parameterized constructor\n";
        }

        Student(const Student & stu, allocator_type alloc)
            : m_name{stu.m_name, alloc} {
                std::cout << "Construtor - Copy constructor\n";
        }

        Student(Student && stu, allocator_type alloc)
            : m_name{std::move(stu.m_name), alloc} {
                std::cout << "Construtor - Move constructor\n";
        }

        void setName(std::pmr::string name) { m_name = std::move(name); }
        std::pmr::string    getName()   const { return m_name; }
        std::string         getNameAsString()   const { return std::string{m_name}; }
    };
}

int main() {

    {
        std::string stdstr{"this is a std string, which will require memory allocation"};
        std::cout << "stdstr: " << stdstr << '\n';
        
        std::pmr::string pmrstr1{stdstr};
        std::cout << "pmrstr1: " << pmrstr1 << '\n';
        
        //std::pmr::string pmrstr2 = stdstr;  // CE error: conversion from 'basic_string<[...],[...],std::allocator<char>>' to non-scalar type 'basic_string<[...],[...],std::pmr::polymorphic_allocator<char>>' requested
        
        std::pmr::string pmrstr3{"this is a pmr string, which will require memory allocation"};
        std::cout << "pmrstr3: " << pmrstr3 << '\n';

        stdstr = pmrstr3;
        std::cout << "stdstr: " << stdstr << '\n';
        std::cout << "pmrstr3: " << pmrstr3 << '\n';
        
        pmrstr3 = stdstr;
        std::cout << "stdstr: " << stdstr << '\n';
        std::cout << "pmrstr3: " << pmrstr3 << '\n';        
    }

    {
        std::cout << "\n==========\n";
        std::string stdstr{"this is a std string, which will require memory allocation"};
        
        //nonstd::Student stu(stdstr);    //  CE error: no matching function for call to 'nonstd::Student::Student(std::string&)'
        //nonstd::Student stu = stdstr;     // CE error: conversion from 'std::string' {aka 'std::__cxx11::basic_string<char>'} to non-scalar type 'nonstd::Student' requested
        nonstd::Student stu{std::pmr::string{stdstr}};  // OK (implicitly converts stdstr to string_view)
    }
    return 0;
}

/**********
    END OF FILE
*************/


