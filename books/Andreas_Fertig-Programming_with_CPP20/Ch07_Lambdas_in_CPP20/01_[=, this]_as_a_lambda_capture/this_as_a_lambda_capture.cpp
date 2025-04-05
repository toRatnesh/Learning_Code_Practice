/*****

References

    Programming with C++20 | Andreas Fertig
	

Chapter 7 | Lambdas in C++20: New features
	
	There are several changes therein to make lambdas even more powerful.

7.1 [=, this] as a lambda capture

	Lambdas are a handy helper whenever we need to create a new type with only a subset of values and a specific action.

	= stands for capture-by-copy, while & donates to capture by-reference
	capture-by-copy means that a certain variable c is copied into the lambda, and with that an independent exact copy of the original c

	Inside member function = copies this rather than any member value making the lambda point to the class, and not a single member
	Let’s call the captured one __this
	This implicit capture of the this-pointer can be a problem, for instance, if we accidentally return this lambda and the class itself goes out of scope
	The data to which __this points to is no longer valid
	As soon as one accesses the contents of the lambda, it is UB

	C++17 capture *this
	C++17 new capture variant *this, which stands for capturing the dereferenced this
	The lambda then contains a deep copy of this, and not just a duplication of the pointer

	However, there is now an asymmetry.
	Consider a code-review situation and you are about to review the code with the lambda in a class.
	You cannot be sure that the code does what we intend it to.

	C++20 adds this missing piece by adding an additional capture option this.
	Now we can express whether the capture of this is just the pointer or a deep copy.
	we need to update the capture clause from [=] to [=, this]

	The behavior that = implies an implicit capture of this is deprecated with C++20.

**********/

#include <iostream>
#include <string>
#include <thread>

class Person {
    std::string     m_name;
    public:
    Person(std::string name) : m_name(name) { }
    
    auto display() {
        
        //auto lambda_inside_memfun = [=] { std::cout << m_name << '\n'; };     // C++14 capture this
        //auto lambda_inside_memfun = [*this] { std::cout << m_name << '\n'; };   // C++17 capture *this
        
        // C++20 warning: implicit capture of 'this' via '[=]' is deprecated in C++20
        //auto lambda_inside_memfun = [=] { std::cout << m_name << '\n'; };

        //auto lambda_inside_memfun = [=, this] { std::cout << m_name << '\n'; };   // C++20 pointer copy
        auto lambda_inside_memfun = [=, *this] { std::cout << m_name << '\n'; };    // C++20 deep copy

        return lambda_inside_memfun;
    }
};

int main() {
    std::thread thr;
    {
        Person p("Person-1");
        auto lambda = p.display();
    
        thr = std::thread(lambda);
    }
    if(thr.joinable()) {
        thr.join();
    }

	return 0;
}

/*****
    END OF FILE
**********/

