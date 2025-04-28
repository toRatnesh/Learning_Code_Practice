/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/reference#Rvalue_references

	https://en.cppreference.com/w/cpp/utility/move
	https://en.cppreference.com/w/cpp/utility/forward


Item 26: Avoid overloading on universal references

	template<typename T>
	void logAndAdd(T&& name);

	void logAndAdd(int idx);

	short nameIdx;
	logAndAdd(nameIdx);		// error!


	The one taking a universal reference can deduce T to be short, thus yielding an exact match. 
	The overload with an int parameter can match the short argument only with a promotion. 
	Per the normal overload resolution rules, an exact match beats a match with a promotion, 
	so the universal reference overload is invoked.
	
	Functions taking universal references are the greediest functions in C++.
	They instantiate to create exact matches for almost any type of argument.
	
	
Wrting constructor taking universal reference
	This is much worse idea
	See example


	class Person {
	public:
		template<typename T>
		explicit Person(T&& n)			// perfect forwarding ctor;
		: name(std::forward<T>(n)) {}	// initializes data member
		
		explicit Person(int idx)		// int ctor
		: name(nameFromIdx(idx)) {}
		…
		private:
		std::string name;
	};
	
	In situations where a template instantiation and a non-template function (i.e., a “normal” function) 
	are equally good matches for a function call, the normal function is preferred
	
	why compilers generate a copy constructor when they could instantiate a templatized constructor 
	to get the signature that the copy constructor would have?
	
	when inheritance enters the picture
	In particular, the conventional implementations of derived class copy and move operations behave quite surprisingly
	
	class SpecialPerson: public Person {
	public:
		SpecialPerson(const SpecialPerson& rhs)	// copy ctor; calls
		: Person(rhs)							// base class
		{ … }									// forwarding ctor!
		
		SpecialPerson(SpecialPerson&& rhs)		// move ctor; calls
		: Person(std::move(rhs))				// base class
		{ … }									// forwarding ctor!
	};
	
	derived class copy and move constructors don’t call their base class’s copy and move constructors, 
	they call the base class’s perfectforwarding constructor
	
	note that the derived class functions are using arguments of type SpecialPerson to pass to their base class, 
	then work through the template instantiation and overload-resolution consequences for the constructors in class Person. 
	Ultimately, the code won’t compile, because there’s no std::string constructor taking a SpecialPerson
	
	
Summary
	•	Overloading on universal references almost always leads to 
		the universal reference overload being called more frequently than expected.
	•	Perfect-forwarding constructors are especially problematic, because 
		they’re typically better matches than copy constructors for non-const lvalues, 
		and they can hijack derived class calls to base class copy and move constructors.

**********/

#include <iostream>
#include <utility>
#include <vector>
#include <cstdint>

class St {
    static int     count;

    int val;
    public:
    ~St()   { ++count; std::puts("~St()"); }
    St()   { std::puts("St()"); }
    
    St(const St & other) : val(other.val) { 
        std::puts("St(const St & other)"); 
    }
    St & operator=(const St & other) { 
        std::puts("operator=(const St & other)"); 

        if(this != &other) {
            val = other.val;
        }
        return *this;
    }

    St(St && other) : val(std::move(other.val)) { 
        std::puts("St(St && other)"); 
    }
    St & operator=(St && other) { 
        std::puts("operator=(St && other)"); 

        if(this != &other) {
            val = std::move(other.val);
        }
        return *this;
    }  

    static void showCount() {
        std::puts(std::to_string(count).c_str());
    }  
    static void resetCount() {
        count = 0;
    } 
};
int     St::count = 0;

void storeStUsingLvalue(const St & st) {
    std::puts("Enter: storeStUsingLvalue(const St & st)");
    static std::vector<St>  lvec;
    lvec.emplace_back(st);
}

template<typename T>
void storeStUsingUniversalRef(T && st) {
    std::puts("Enter: storeStUsingUniversalRef(T && st)");
    static std::vector<St>  lvec;
    lvec.emplace_back(st);
}

void overloadOnUniversal(const int val) {
    std::puts("overloadOnUniversal(const int val)");
}

template<typename T>
void overloadOnUniversal(T && val) {
    std::puts("overloadOnUniversal(T && val)");
}

class UsePerfectForwardingConstructor {
    St      mst;
    public:
    UsePerfectForwardingConstructor() { }

    template<typename T>
    explicit UsePerfectForwardingConstructor(T && val) 
    : mst(std::forward<T>(val)) {
        std::puts("UsePerfectForwardingConstructor(T && val) ");
    }
};

class Base {
    St      mst;
};

class Derived1 : public Base {
    public:
    Derived1() {    }
    Derived1(const Derived1 & other) : Base{other}  {     }
    Derived1(Derived1 && other) : Base{std::move(other)} {  }   
};

class Derived2 : public UsePerfectForwardingConstructor {
    public:
    Derived2() {    }
    // error: no matching function for call to 'St::St(const Derived2&)'
    //Derived2(const Derived2 & other) : UsePerfectForwardingConstructor{other}  {     }
    
    // error: no matching function for call to 'St::St(Derived2)'
    //Derived2(Derived2 && other) : UsePerfectForwardingConstructor{std::move(other)} {  } 
};

int main() {

    {   std::puts("=== Using lvalue ref ===");
        St st;
        storeStUsingLvalue(st);
        storeStUsingLvalue(std::move(st));
        storeStUsingLvalue(St{});
    }
    St::showCount();
    St::resetCount();
    
    {   std::puts("\n=== Using universal ref ===");
        St st;
        storeStUsingUniversalRef(st);
        storeStUsingUniversalRef(std::move(st));
        storeStUsingUniversalRef(St{});
    }    
    St::showCount();
    St::resetCount();

    {   std::puts("\n=== Overloading on universal ref ===");
        int val = 10;
        const int cval = 15;

        overloadOnUniversal(val);
        overloadOnUniversal(cval);

        uint32_t    u32val1 = 5;
        const uint32_t    u32val2 = 7;

        overloadOnUniversal(u32val1);
        overloadOnUniversal(u32val2);

        long int lval = 5;
        const long int clval = 9;

        overloadOnUniversal(lval);
        overloadOnUniversal(clval);        
    }

    {   std::puts("\n=== Use Perfect Forwarding Constructor ===");
        {   std::puts("--- copying non const object ---");
            UsePerfectForwardingConstructor pfc1{St{}};
            
            // error: no matching function for call to 'St::St(UsePerfectForwardingConstructor&)'
            // UsePerfectForwardingConstructor pfc2{pfc1};        
        }
        {   std::puts("--- copying const object ---");
            const UsePerfectForwardingConstructor pfc1{St{}};
            // calls the compiler generated copy constructor
            UsePerfectForwardingConstructor pfc2{pfc1};
        } 
        {   std::puts("--- moving non const object ---");
            UsePerfectForwardingConstructor pfc1{St{}};
            // calls the compiler generated move constructor
            UsePerfectForwardingConstructor pfc2{std::move(pfc1)};
        }  
        {   std::puts("--- moving const object ---");
            const UsePerfectForwardingConstructor pfc1{St{}};
            // error: no matching function for call to 'St::St(const UsePerfectForwardingConstructor)'
            // UsePerfectForwardingConstructor pfc2{std::move(pfc1)};
        }                        
    }

    {   std::puts("\n=== Use Perfect Forwarding Constructor in case of inheritance ===");
        {   std::puts("--- using conventional inheritance ---");
            Derived1    d1;
            Derived1    d2{d1};
            Derived1    d3{std::move(d1)};        
        }
        {   std::puts("--- can not use inheritance from base using perfect forward constructor ---");
            Derived2    d1{};
            //Derived2    d2{d1};
            //Derived2    d3{std::move(d1)};        
        }        
    }

    std::puts("\n=== END OF MAIN ===");
    return 0;
}

/*****
    END OF FILE
**********/


