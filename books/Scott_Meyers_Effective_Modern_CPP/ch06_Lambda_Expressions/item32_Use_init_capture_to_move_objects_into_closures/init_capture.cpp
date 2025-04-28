/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/lambda


Item 32: Use init capture to move objects into closures

	C++11 lambda offers no way to get move-only object into a closure
	C++14 lambda offers support to move objects into a closure

C++14 lambda init capture (or generalized lambda capture)

	It can do virtually everything the C++11 capture forms can do, plus more.
	The one thing you can’t express with an init capture is a default capture mode,

	Using an init capture makes it possible for you to specify
		1.	the name of a data member in the closure class generated from the lambda and
		2.	an expression initializing that data member.

	[lambda_var = local_var]() { };
	
	To the left of the “=”
		name of the data member in the closure class
		scope of the closure class
	To the right of the “=”
		initializing expression
		scope same where the lambda is being defined
		
	code in the body of the lambda is in the scope of the closure class, 
	so it refer to the closure class data member

C++11 work-around
	1.	Write your own closure class
	2.	If you want to stick with lambdas, move capture can be emulated in C++11
		i.	moving the object to be captured into a function object produced by std::bind and
		ii.	giving the lambda a reference to the “captured” object
		
	Because a bind object stores copies of all the arguments passed to std::bind, 
	the bind object in our example contains a copy of the closure produced by the lambda. 
	The lifetime of the closure is therefore the same as the lifetime of the bind object.
	
	See example code below
	
Summary
	•	Use C++14’s init capture to move objects into closures.
	•	In C++11, emulate init capture via hand-written classes or std::bind.

**********/

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

int main() {
    
    {   std::puts("=== Using C+14 lambda init capture or genralized lambda capture ===");
        const std::string str{"Moving a unique pointer inside lambda"};
        static int rand_val = 3;
        auto lp = std::make_unique<int>(5);

        auto lambda = [=, ptr = std::move(lp)](const int mul) { 
           std::puts(str.c_str());
            return ((*ptr) * mul * rand_val);
        };

        rand_val = rand_val + 2;

        std::cout << lambda(2) << '\n';
    }

    {   std::puts("\n=== Using C+11 bind to achieve equivelent of C++14 lambda init capture ===");
        const std::string str{"Moving a unique pointer inside lambda"};
        static int rand_val = 3;
        auto lp = std::unique_ptr<int>(new int{5});

        auto func = std::bind([=](const std::unique_ptr<int>& ptr, const int mul) { 
            std::puts(str.c_str());
            return ((*ptr) * mul * rand_val);
        }, std::move(lp), std::placeholders::_1);

        rand_val = rand_val + 2;

        std::cout << func(2) << '\n';
    }

    {   std::puts("\n=== Using self written closure class to achieve equivelent of C++14 lambda init capture ===");
        const std::string str{"Moving a unique pointer inside lambda"};
        static int rand_val = 3;
        auto lp = std::unique_ptr<int>(new int{5});

        class LambdaClosureClass {
            std::unique_ptr<int>    mptr;
            std::string             mstr;

            public:
            LambdaClosureClass(std::unique_ptr<int> && ptr, const std::string & str) 
            : mptr(std::move(ptr)), mstr(str) { }

            
            int operator()(const int mul) { 
                std::puts(mstr.c_str());
                return ((*mptr) * mul * rand_val);
            }
            

        };

        LambdaClosureClass lambda{std::move(lp), str};

        rand_val = rand_val + 2;

        std::cout << lambda(2) << '\n';

    }

    return 0;
}

/*****
    END OF FILE
**********/


