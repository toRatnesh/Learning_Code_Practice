/*****

References
    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/types/type_info
    https://en.cppreference.com/w/cpp/language/typeid

Item 4: Know how to view deduced types

IDE Editors
	Code editors in IDEs often show the types of program entities (e.g., variables, parameters, functions, etc.) 
	when you do something like hover your cursor over the entity

    For this to work, your code must be in a more or less compilable state, 
    because what makes it possible for the IDE to offer this kind of information 
    is a C++ compiler running inside the IDE.	

Compiler Diagnostics
	use a type in a way that leads to compilation problems
	The error message reporting the problem is virtually sure to mention the type that’s causing it

Runtime Output
	The printf approach to displaying type information can’t be employed until runtime
	To create a textual representation typeid and std::type_info::name is used
	Calls to std::type_info::name are not guaranteed to return anything sensible, some compiler may return mangled names
	
	The results of std::type_info::name are not reliable
    Consider a more complex example: (Below code of displayType())
    Param’s type—which is const Student * const &—is reported as const Student*.

	The specification for std::type_info::name mandates that the type be treated as 
	if it had been passed to a template function as a by-value parameter. 
	As Item 1 explains, that means that if the type is a reference, 
	its reference-ness is ignored, and if the type after reference removal is 
	const (or volatile), its constness (or volatileness) is also ignored
	


	Where std::type_info::name and IDEs may fail, the Boost TypeIndex library is designed to succeed
	

Summary:
	-> Deduced types can often be seen using IDE editors, compiler error messages, and the Boost TypeIndex library
	-> The results of some tools may be neither helpful nor accurate, so an understanding of C++’s type deduction rules remains essential
	-> Where std::type_info::name and IDEs may fail, the Boost TypeIndex library is designed to succeed

**********/

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

#include <boost/type_index.hpp>

template<typename T>
class TD;

struct Student {
    std::string name;
    std::string address;
    double age;
};

template<typename T>
void displayType(const T & param) { 

    std::cout << "T = " << typeid(T).name() << '\n';
    std::cout << "param = " << typeid(param).name() << '\n';

    std::puts("--- using boost name ---");
    std::cout << "T = " << boost::typeindex::type_id_with_cvr<T>().name() << '\n';
    std::cout << "param = " << boost::typeindex::type_id_with_cvr<decltype(param)>().name() << '\n';

    std::puts("--- using boost pretty_name ---");
    std::cout << "T = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << '\n';
    std::cout << "param = " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
    
}

std::vector<Student> getStudentVec() {
    Student st1{"Student-1", "Address-1", 13};
    Student st2{"Student-2", "Address-2", 15};
    return {st1, st2};
}

int main() {

    {
        std::puts("=== Compiler Diagnostics ===");
        const int ival = 23;
        auto a1 = ival;
        auto a2 = &ival;

        //TD<decltype(a1)> a1_type;   // CE error: aggregate 'TD<int> a1_type' has incomplete type and cannot be defined
        //TD<decltype(a2)> a2_type;   // CE error: aggregate 'TD<int*> a2_type' has incomplete type and cannot be defined
    }

    {
        std::puts("=== Runtime Output ===");
        const int ival = 23;
        auto a1 = ival;
        auto a2 = &ival;

        std::cout << typeid(a1).name() << '\n';
        std::cout << typeid(a2).name() << '\n';

        const auto st_vec= getStudentVec();

        if(not st_vec.empty()) {
            displayType(&st_vec[0]);
        }
    }

    return 0; 
}

/*****
    END OF FILE
**********/


