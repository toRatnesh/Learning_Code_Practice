/*****

References

    Effective Modern C++ | Scott Meyers
	https://en.cppreference.com/w/cpp/language/reference
	https://en.cppreference.com/w/cpp/language/sfinae
	https://en.cppreference.com/w/cpp/types/enable_if

Item 27: Familiarize yourself with alternatives to overloading on universal references

	1.	Abandon overloading
	2.	Pass by const T&
	3.	Pass by value
	4.	Use Tag dispatch
	5.	Constraining templates that take universal references

1.	Abandon overloading
	Instead of overloading on universal references use different names for the would-be overloads
	drawback:
	won’t work for the special member functions like copy and move operations

2.	Pass by const T&
	revert to C++98 and replace pass-by-universal-reference with pass-by-lvalue-reference-to-const
	drawback:
	the design isn’t as efficient as we’d prefer
	giving up some efficiency to keep things simple might be a more attractive trade-off than it initially appeared

3.	Pass by value
	To dial up performance without any increase in complexity is to 
	replace pass-by-reference parameters with, counterintuitively, pass by value
	
	The design adheres to the advice in Item 41 to 
	consider passing objects by value when you know you’ll copy them

4.	Use Tag dispatch
	With both overloading and universal references present, how can we avoid overloading on universal references?
	A universal reference parameter generally provides an exact match for whatever’s passed in, 
	but if the universal reference is part of a parameter list containing other parameters that are not universal references, 
	sufficiently poor matches on the non-universal reference parameters can 
	knock an overload with a universal reference out of the running. 
	That’s the basis behind the tag dispatch approach, see example code below
	
	Consider a function is overloaded for universal parameter and int parameter
	
	Rather than adding the overload, we’ll reimplement the function to delegate to two other functions, 
	one for integral values and one for everything else. 
	the function itself will accept all argument types, both integral and non-integral.
	
	we need to use overload resolution a compile time phenomenon to choose the correct function overload.
	That means we need a type that corresponds to true and a different type that corresponds to false.
	The Standard Library provides what is required under the names std::true_type and std::false_type.
	
	In this design, the types std::true_type and std::false_type are “tags”
	whose only purpose is to force overload resolution to go the way we want.
	
	They serve no purpose at runtime, and in fact we hope that compilers will recognize that 
	the tag parameters are unused and will optimize them out of the program’s execution image
	
	The call to the overloaded implementation functions inside logAndAdd “dispatches” 
	the work to the correct overload by causing the proper tag object to be created. 
	Hence the name for this design: tag dispatch. 
	
	It’s a standard building block of template metaprogramming, 
	and the more you look at code inside contemporary C++ libraries, the more often you’ll encounter it.

5.	Constraining templates that take universal references
	For situations like, where an overloaded function taking a universal reference is greedier than you want, 
	yet not greedy enough to act as a single dispatch function, tag dispatch is not suitable
	You need a different technique, one that lets you rachet down the conditions under which 
	the function template that the universal reference is part of is permitted to be employed.
	
	std::enable_if
	By default, all templates are enabled, but a template using std::enable_if is 
	enabled only if the condition specified by std::enable_if is satisfied,
	otherwise, it is said to be disabled.
	
	SFINAE is the technology that makes std::enable_if work
	
	General syntax is 
	template<typename T, typename = typename std::enable_if<condition>::type>	// SFINAE USING std::enable_if
	explicit Person(T&& n);

	We can thus constrain universal reference construtor to not accpet Person,
	any type derived from Person and integral in following way

	template<
		typename T,
			typename = std::enable_if_t<
			!std::is_base_of<Person, std::decay_t<T>>::value
			&&
			!std::is_integral<std::remove_reference_t<T>>::value
		>
	>
	explicit Person(T&& n);
	
	Because it uses perfect forwarding, it offers maximal efficiency, and because 
	it controls the combination of universal references and overloading rather than forbidding it,
	this technique can be applied in circumstances (such as constructors) where overloading is unavoidable.	

Trade-offs
	abandoning overloading, passing by const T&, and passing by value—
	specify a type for each parameter in the function(s) to be called
	
	tag dispatch and constraining template eligibility—use perfect forwarding, 
	hence don’t specify types for the parameters
	
	As a rule, perfect forwarding is more efficient, because it avoids the creation of temporary objects 
	solely for the purpose of conforming to the type of a parameter declaration.
	Drawbacks
	1.	some kinds of arguments can’t be perfect-forwarded, 
		even though they can be passed to functions taking specific types
	2.	The comprehensibility of error messages when clients pass invalid arguments
	
Summary
	•	Alternatives to the combination of universal references and overloading include 
		the use of distinct function names, passing parameters by lvaluereference- to-const, 
		passing parameters by value, and using tag dispatch.
	•	Constraining templates via std::enable_if permits the use of universal references and overloading together, 
		but it controls the conditions under which compilers may use the universal reference overloads.
	•	Universal reference parameters often have efficiency advantages, but they typically have usability disadvantages.

**********/

#include <iostream>
#include <set>
#include <cstdint>
#include <type_traits>

class St {
    int val;
    public:
    ~St()   { std::puts("~St()"); }
    St()   { std::puts("St()"); }
    St(const int val) : val(val)   { std::puts("St(const int val)"); }
    
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
    bool operator<(const St & other) const {
        return val < other.val;
    }    
};

std::multiset<St>    st_set;

void insertInSet(const int val) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(val);
}

template<typename T>
void insertInSet(T&& val) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(std::forward<T>(val));
}

template<typename T>
void useConstRef(const T& val) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(val);
}


void useByValue(const int val) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(val);
}



template<typename T>
void useTagDispatchHelper(T&& val, std::false_type) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(std::forward<T>(val));
}

template<typename T>
void useTagDispatchHelper(T&& val, std::true_type) {
    std::puts(__PRETTY_FUNCTION__);
    st_set.emplace(val);
}

template<typename T>
void useTagDispatch(T&& val) {
    std::puts(__PRETTY_FUNCTION__);
    useTagDispatchHelper(val, std::is_integral<T>{});
}



class Base {
    St mst;

   public:
   Base() {  std::puts("Base()"); }

   template <typename T, 
            typename = 
            std::enable_if_t< 
                (not std::is_base_of<Base, std::decay_t<T>>::value)
            >
    >
    explicit Base(T&& val)
        : mst(std::forward<T>(val)) {
        std::puts("Base(T && val) ");
    }
};

class Derived : public Base {
    public:
    ~Derived() {    std::puts("~Derived()"); }
    Derived() {    std::puts("Derived()"); }
    
    Derived(const Derived & other) : Base{other}  {     
        std::puts("Derived(const Derived & other)");
    }
    Derived& operator=(const Derived & other) {
        Base::operator=(other);
        std::puts("operator=(const Derived & other)");
        return *this;
    }

    Derived(Derived && other) : Base(std::move(other)) {  
        std::puts("Derived(Derived && other)");
    }
    Derived& operator=(Derived && other) {
        Base::operator=(std::move(other));
        std::puts("operator=Derived(Derived && other)");

        return *this;
    }     
};

int main() {
    {   std::puts("=== Issue with overloading ===");
        insertInSet(5);
        const int ival = 6;
        insertInSet(ival);

        const unsigned int uval = 7;
        insertInSet(uval);      // invokes template version
    }

    {   std::puts("\n=== 1. Abandon overloading ===");    
        std::puts("Removing overload void insertInSet(const int val) will cause only to invoke template version");
    }

    {   std::puts("\n=== 2. Pass by const T& ===");
        useConstRef(5);

        const int ival = 6;
        useConstRef(ival);

        const unsigned int uval = 7;
        useConstRef(uval);
    }

    {   std::puts("\n=== 3. Pass by value ===");
        useByValue(5);

        const int ival = 6;
        useByValue(ival);

        const unsigned int uval = 7;
        useByValue(uval);    
    }
    
    {   std::puts("\n=== 4. Use Tag dispatch ===");

        useTagDispatch(5);

        const int ival = 6;
        useTagDispatch(ival);

        const unsigned int uval = 7;
        useTagDispatch(uval);  
    }
    
    {   std::puts("\n=== 5. Constraining templates that take universal references ===");
        Derived     d1;
        Derived     d2{d1};
        d2 = d1;
        Derived     d3{std::move(d1)};
        d3 = std::move(d2);
    }

    std::puts("\n=== END OF MAIN ===");

    return 0;
}

/*****
    END OF FILE
**********/


