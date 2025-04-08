/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/nullptr
    https://en.cppreference.com/w/cpp/types/nullptr_t

Item 8: Prefer nullptr to 0 and NULL

	C++’s primary policy is that 0 is an int, not a pointer.
	There is some uncertainty in the details in NULL’s case, 
	because implementations are allowed to give NULL an integral type other than int (e.g., long).

	neither 0 nor NULL has a pointer type

In C++98,
	overloading on pointer and integral types could lead to surprises
	Passing 0 or NULL to such overloads never called a pointer overload

		void f(int);	// three overloads of f
		void f(bool);
		void f(void*);

		f(0);		// calls f(int), not f(void*)
		f(NULL);	// might not compile, but typically calls f(int). Never calls f(void*)

	This counterintuitive behavior is what led to the guideline for 
	C++98 programmers to avoid overloading on pointer and integral types.
	That guideline remains valid in C++11,


nullptr

	nullptr’s advantage is that it doesn’t have an integral type. 

	To be honest, it doesn’t have a pointer type, either, but you can think of it as a pointer of all types.
	nullptr’s actual type is std::nullptr_t, and, in a wonderfully circular definition, 
	std::nullptr_t is defined to be the type of nullptr.

	The type std::nullptr_t implicitly converts to all raw pointer types, 
	and that’s what makes nullptr act as if it were a pointer of all types.

		f(nullptr); // calls f(void*) overload
		
	Using nullptr instead of 0 or NULL thus avoids overload resolution surprises

	It can also improve code clarity, especially when auto variables are involved.

	nullptr shines especially brightly when templates enter the picture
	With nullptr, templates pose no special challenge.
	Combined with the fact that nullptr doesn’t suffer from the overload resolution surprises 
	that 0 and NULL are susceptible to, the case is ironclad. 

	When you want to refer to a null pointer, use nullptr, not 0 or NULL.

**********/

#include <iostream>
#include <memory>

void fun(int val) {
    std::cout << __func__ << " taking int: " << val << '\n';
}

void fun(bool val) {
    std::cout << std::boolalpha << __func__ << " taking bool: " << val << '\n';
}

void fun(void * ) {
    std::cout << __func__  << " taking void * \n";
}

int * funReturningPointer() {
    return nullptr;
}

int funReturningInteger() {
    return 3;
}


struct Athing {};

int usingSharedPointer(std::shared_ptr<Athing> sp) {
    int retval = 0;
    if(sp) {
        retval = 10;
    } else {
        retval = 20;
    }

    return retval;
}

double usingUniquePointer(std::unique_ptr<Athing> sp) {
    double retval = 0;
    if(sp) {
        retval = 11.23;
    } else {
        retval = 24.56;
    }

    return retval;
}

bool usingRawPointer(Athing * ptr) {
    bool retval = false;
    if(ptr) {
        retval = true;
    } else {
        retval = false;
    }
    return retval;
}

/*
    WHEN USING TEMPLATE IMPLICIT CONVERSION FROM 0 AND NULL TO POINTER WILL NOT TAKE PLACE
    THUS WE WILL NOT BE ABLE TO USE 0 AND NULL AS POINTER
    ONLY nullptr WILL WORK IN THIS CASE
*/
template<typename Func, typename Ptr>
decltype(auto) usePointerUsingTemplate(Func fun, Ptr ptr) {
    return fun(ptr);
}

int main() {

    {
        std::cout << "=== Calling overloaded function with 0, NULL and nullptr ===\n";
        fun(0);
        //fun(NULL);  // error: call to 'fun' is ambiguous
        fun(nullptr);
    }

    {
        std::cout << "=== For auto return value comparing with 0 for integeral and pointer return type ===\n";
        // when using auto and comparing with 0 can not be clear if variable is integeral or pointer 
        auto res = funReturningPointer();
        if(0 == res) {
            std::cout << "Return type is pointer, Result is 0\n";
        }
        else {
            std::cout << "Return type is pointer, Result is not 0\n";
        }

        auto res2 = funReturningInteger();
        if(0 == res2) {
            std::cout << "Return type is integral, Result is 0\n";
        }
        else {
            std::cout << "Return type is integral, Result is not 0\n";
        }       
    }

    {
        std::cout << "=== For auto return value comparing with 0 for integeral and nullptr for pointer return type ===\n";
        // when using auto and comparing with nullptr it will always be pointer
        auto res = funReturningPointer();
        if(nullptr == res) {
            std::cout << "Return type is pointer, Result is 0\n";
        }
        else {
            std::cout << "Return type is pointer, Result is not 0\n";
        }

        auto res2 = funReturningInteger();
        if(0 == res2)
        //if(nullptr == res2)   error: invalid operands of types 'std::nullptr_t' and 'int' to binary 'operator=='
        {
            std::cout << "Return type is integral, Result is 0\n";
        }
        else {
            std::cout << "Return type is integral, Result is not 0\n";
        }        
    }

    {
        std::cout << "=== Using 0, NULL and nullptr with template ===\n";
        {
            auto res1 = usingSharedPointer(0);
            auto res2 = usingSharedPointer(NULL);
            auto res3 = usingSharedPointer(nullptr);
        }

        {
            auto res1 = usingUniquePointer(0);
            auto res2 = usingUniquePointer(NULL);
            auto res3 = usingUniquePointer(nullptr);
        }  
        {
            auto res1 = usingRawPointer(0);
            auto res2 = usingRawPointer(NULL);
            auto res3 = usingRawPointer(nullptr);
        }

        {
            // CE error: could not convert 'ptr' from 'int' to 'std::shared_ptr<Athing>'
            //auto res1 = usePointerUsingTemplate(usingSharedPointer, 0); 

            // CE error: could not convert 'ptr' from 'long int' to 'std::shared_ptr<Athing>'
            //auto res2 = usePointerUsingTemplate(usingSharedPointer, NULL);

            auto res3 = usePointerUsingTemplate(usingSharedPointer, nullptr);
        } 

        {
            // CE error: error: could not convert 'ptr' from 'int' to 'std::unique_ptr<Athing>'
            //auto res1 = usePointerUsingTemplate(usingUniquePointer, 0); 

            // CE error: error: could not convert 'ptr' from 'long int' to 'std::unique_ptr<Athing>'
            //auto res2 = usePointerUsingTemplate(usingUniquePointer, NULL);

            auto res3 = usePointerUsingTemplate(usingUniquePointer, nullptr);
        } 

        {
            // CE error: error: invalid conversion from 'int' to 'Athing*' [-fpermissive]
            //auto res1 = usePointerUsingTemplate(usingRawPointer, 0); 

            // CE error: error: invalid conversion from 'long int' to 'Athing*' [-fpermissive]
            //auto res2 = usePointerUsingTemplate(usingRawPointer, NULL);

            auto res3 = usePointerUsingTemplate(usingRawPointer, nullptr);
        }
    }


    return 0; 
}

/*****
    END OF FILE
**********/

