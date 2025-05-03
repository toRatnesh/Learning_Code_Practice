/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/container/vector

Item 42: Consider emplacement instead of insertion

	Emplacement functions can thus do everything insertion functions can.
	They sometimes do it more efficiently, and, at least in theory, they should never do it less efficiently.

	to determine whether emplacement or insertion runs faster, benchmark them both

	If all the following are true, emplacement will almost certainly outperform insertion:

	•	The value being added is constructed into the container, not assigned.
		when the value being added is put into the container via assignment, emplacement’s edge tends to disappear
		Node-based containers virtually always use construction to add new values,

	•	The argument type(s) being passed differ from the type held by the container.
	•	The container is unlikely to reject the new value as a duplicate.	

	In the emplacement functions, perfect-forwarding defers the creation of the resource-managing objects until 
	they can be constructed in the container’s memory, and that opens a window during which exceptions can lead to resource leaks.

explicit constructors

	std::regex r1 = nullptr;	// copy initialization, error! won't compile
	std::regex r2(nullptr);		// Direct initialization, compiles	

	Copy initialization is not permitted to use explicit constructors. Direct initialization is.

	Emplacement functions use direct initialization, which means they may use explicit constructors.
	Insertion functions employ copy initialization, so they can’t.

	when you use an emplacement function, be especially careful to make sure you’re passing the correct arguments, 
	because even explicit constructors will be considered by compilers as they try to find a way to interpret your code as valid.

Summary
•	In principle, emplacement functions should sometimes be more efficient 
	than their insertion counterparts, and they should never be less efficient. 
	
•	In practice, they’re most likely to be faster when
	1.	the value being added is constructed into the container, not assigned;
	2.	the argument type(s) passed differ from the type held by the container; and
	3.	the container won’t reject the value being added due to it being a duplicate.
	
•	Emplacement functions may perform type conversions that would be rejected by insertion functions.

**********/

#include <iostream>
#include <vector>

class St {

    int     val;
    public:
    
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    explicit St(int val) : val(val)  { std::puts("St(int)"); }
    
    St(const St & other) noexcept : val(other.val) { 
        std::puts("St(const St & other)");
    }
    St & operator=(const St & other) noexcept { 
        std::puts("operator=(const St & other)");

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) noexcept : val(std::move(other.val)) { 
        std::puts("St(St && other)");
    }
    St & operator=(St && other) noexcept { 
        std::puts("operator=(St && other)");

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

};

int main() {

    std::vector<St>     lvec;
    lvec.reserve(10);

    {   std::puts("=== using push_back ===");
        St st;
        lvec.push_back(st);         // St(const St & other)
        lvec.push_back(St{});       // St(), St(St && other)   
        
        //lvec.push_back(5);          // St(int), St(St && other),  WITHOUT EXPLICIT
        //lvec.push_back(5);          // WITH EXPLICIT, error: no matching function for call to 'std::vector<St>::push_back(int)'

        //lvec.push_back(8.9);        // St(int), St(St && other),  WITHOUT EXPLICIT
        //lvec.push_back(8.9);        // WITH EXPLICIT, error: no matching function for call to 'std::vector<St>::push_back(double)'
        
    }

    {   std::puts("\n=== using emplace_back ===");
        St st;
        lvec.emplace_back(st);         // St(const St & other)
        lvec.emplace_back(St{});       // St(), St(St && other)   
        lvec.emplace_back(5);          // St(int)
        lvec.emplace_back(8.9);        // St(int)
    }

    std::puts("\n=== END OF MAIN ===");
    return 0;
}

/*****
    END OF FILE
**********/

