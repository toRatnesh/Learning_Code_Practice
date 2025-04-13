/*****

References

    Effective Modern C++ | Scott Meyers

	https://en.cppreference.com/w/cpp/memory/unique_ptr
	https://en.cppreference.com/w/cpp/memory/shared_ptr

	https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
	https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared

Item 21: Prefer std::make_unique and std::make_shared to direct use of new

std::make_shared (since C++11) and std:make_unique (since C++14)
	Advantage:
		reduces object code bloat
		prevent resource leak
		improve performance


	Workaround for C++11 make_unique, This form of the function doesn’t support arrays or custom deleters
	template<typename T, typename... Ts>
	std::unique_ptr<T> make_unique(Ts&&... params) {
		return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
	}


Why prefer make_unique and make_shared

	auto upw1(std::make_unique<Widget>());		// with make func
	std::unique_ptr<Widget> upw2(new Widget);	// without make func

	auto spw1(std::make_shared<Widget>());		// with make func
	std::shared_ptr<Widget> spw2(new Widget);	// without make func	

	1. make functions don't repeat type while other uses it
		Duplication in source code		
			increases compilation times,
			can lead to bloated object code, and generally 
			renders a code base more difficult to work with.
			
	2. exception safety
		Consider following code
		
		void processWidget(std::shared_ptr<Widget> spw, int priority);
		int computePriority();
		processWidget(std::shared_ptr<Widget>(new Widget), computePriority());	// potential resource leak
		
		At runtime, the arguments for a function must be evaluated before the function can be invoked,
		
		Consider, compilers may emit code to execute the operations in this order:
			1. Perform “new Widget”.
			2. Execute computePriority.
			3. Run std::shared_ptr constructor.
		If such code is generated and, at runtime, computePriority produces an exception, 
		the dynamically allocated Widget from Step 1 will be leaked, 
		because it will never be stored in the std::shared_ptr that’s supposed to start managing it in Step 3.
		
		Using std::make_shared avoids this problem
			processWidget(std::make_shared<Widget>(), computePriority());	// no potential resource leak
		
		At runtime, either std::make_shared or computePriority will be called first. 
		
		If it’s std::make_shared, the raw pointer to the dynamically allocated Widget is safely stored in the returned 
		std::shared_ptr before computePriority is called.
		If computePriority then yields an exception, the std::shared_ptr destructor will see to it that the Widget it owns is destroyed. 
		
		And if computePriority is called first and yields an exception, std::make_shared will not be invoked, 
		and there will hence be no dynamically allocated Widget to worry about.

		
std::make_shared improved efficiency
	std::make_shared allows compilers to generate smaller, faster code that employs leaner data structures.
	
	std::shared_ptr<Widget> spw2(new Widget);	// without make func
	it actually performs two memory allocation
	Direct use of new, requires one memory allocation for the Widget and a second allocation for the control block.
	
	auto spw1(std::make_shared<Widget>());		// with make func
	std::make_shared allocates a single chunk of memory to hold both the Widget object and the control block. 
	
	This optimization 
		reduces the static size of the program, because the code contains only one memory allocation call, and 
		it increases the speed of the executable code, because memory is allocated only once.
		
	The efficiency analysis for std::make_shared is equally applicable to std::allocate_shared
	

Drawback of std::make_shared and std::make_unique
	1.	custom deleters not possible
	2.	braced initializers not possible
		creating the object using parentheses calls the non-std::initializer_list constructor
		The make functions perfect-forward their parameters to an object’s constructor
		within the make functions, the perfect forwarding code uses parentheses, not braces
		
		Workaround
		use auto type deduction to create a std::initializer_list object from a braced initializer, 
		then pass the autocreated object through the make function

Drawback of std::make_shared only	
	1.	classes with custom memory management
	
		Often, class-specific operator new and operator delete are designed only to allocate and deallocate 
		chunks of memory of precisely the size of objects of the class
		
		But for std::shared_ptr’s the size of the dynamically allocated object, it’s the size of that object plus the size of a control block
	
	2.	systems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding std::shared_ptrs
		With a direct use of new, the memory for the ReallyBigType object can be released as soon as the last std::shared_ptr to it is destroyed
		

Some info about reference count and weak count
	The control block contains a second reference count, one that tallies how many std::weak_ptrs refer to the control block.
	This second reference count is known as the weak count. When a std::weak_ptr checks to see if it has expired (see Item 19), 
	it does so by examining the reference count (not the weak count) in the control block that it refers to. 
	If the reference count is zero (i.e., if the pointed-to object has no std::shared_ptrs referring to it and has thus been destroyed), 
	the std::weak_ptr has expired. Otherwise, it hasn’t.

	As long as std::weak_ptrs refer to a control block (i.e., the weak count is greater than zero), 
	that control block must continue to exist. 
	And as long as a control block exists, the memory containing it must remain allocated. 
	The memory allocated by a std::shared_ptr make function, then, can’t be deallocated until 
	the last std::shared_ptr and the last std::weak_ptr referring to it have been destroyed.


Summary
	•	Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, 
		and, for std::make_shared and std::allocate_shared, generate code that’s smaller and faster.
	•	Situations where use of make functions is inappropriate include the need to specify custom deleters 
		and a desire to pass braced initializers
	•	For std::shared_ptrs, additional situations where make functions may be ill-advised include 
		(1) classes with custom memory management and 
		(2) systems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding std::shared_ptrs.

**********/

#include <iostream>
#include <memory>
#include <vector>
#include <array>

class St {
    int     val;
    public:
    
    ~St()   { std::cout << "~St() "; }
    St()   { std::cout << "St() "; }
    explicit St(const int ival) : val(ival) { std::cout << "St(const int ival)\n"; }
    
    St(const St & other) : val(other.val) { 
        std::cout << "St(const St & other)\n"; 
    }
    St & operator=(const St & other) { 
        std::cout << "operator=(const St & other)\n"; 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::cout << "St(St && other)\n"; 
    }
    St & operator=(St && other) { 
        std::cout << "operator=(St && other)\n"; 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }    

    operator int() {
        return val;
    }
};

int main() {

    {   std::cout << "=== Using new for shared pointer ===\n";
        std::shared_ptr<St> lsp{new St{5}};
    }

    {   std::cout << "\n=== Using make_shared for shared pointer ===\n";
        auto lsp = std::make_shared<St>(5);
    }

    {   std::cout << "\n=== Using make for initializer list ===\n";
        {
            auto lsp_vec = std::make_unique<std::vector<int>>(10, 20);
            for(auto & elem : *lsp_vec) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';            
        }
        {
            auto linit = {10, 20};
            auto lsp_vec = std::make_unique<std::vector<int>>(linit);
            for(auto & elem : *lsp_vec) {
                std::cout << elem << ' ';
            }
            std::cout << '\n';            
        }
    }

    {   std::cout << "\n=== Using make and new for to create shared pointer for large objects\n";
        using arr_t = std::array<St, 10>;
        {   std::cout << "\n--- using make for shared pointer ---\n";  
            std::weak_ptr<arr_t> lwp;
            {
                auto lsp = std::make_shared<arr_t>();
                lwp = lsp;

                std::cout << "\nshared pointer goes out of scope here\n";
            }
            std::cout << "\nweak pointer goes out of scope here\n";
        }

        {   std::cout << "\n--- using new for shared pointer ---\n";
            std::weak_ptr<arr_t> lwp;
            {
                std::shared_ptr<arr_t> lsp{new arr_t{}};
                lwp = lsp;

                std::cout << "\nshared pointer goes out of scope here\n";
            }
            std::cout << "\nweak pointer goes out of scope here\n";
        }
    }

    return 0;
}

/*****
    END OF FILE
**********/


