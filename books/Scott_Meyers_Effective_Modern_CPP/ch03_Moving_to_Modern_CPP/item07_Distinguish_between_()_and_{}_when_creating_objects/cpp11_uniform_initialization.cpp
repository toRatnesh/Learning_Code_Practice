/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/initialization

Item 7: Distinguish between () and {} when creating objects

C++ initialization:
	As a general rule,
	initialization values may be specified with parentheses, an equals sign, or braces:
		int x(0);	// initializer is in parentheses
		int y = 0;	// initializer follows "="
		int z{0};	// initializer is in braces

	In many cases, it’s also possible to use an equals sign and braces together:
		int z = {0};	// initializer uses "=" and braces

	the use of an equals sign for initialization often misleads C++ newbies into thinking 
	that an assignment is taking place, even though it’s not.
		Widget w1;		// call default constructor
		Widget w2 = w1;	// not an assignment; calls copy ctor
		w1 = w2;		// an assignment; calls copy operator=

C++11 uniform initialization:
	a single initialization syntax that can, at least in concept, be used anywhere and express everything.
	“Uniform initialization” is an idea. “Braced initialization” is a syntactic construct.

	Braces and “=” initialization syntax can also be used to specify 
	default initialization values for non-static data members, but parentheses can not be
		class Widget {
			…
			private:
			int x{ 0 };	// fine, x's default value is 0
			int y = 0;	// also fine
			int z(0);	// error!
		};

	uncopyable objects (e.g., std::atomics) may be initialized using braces or parentheses, but not using “=”
		std::atomic<int> ai1{0};	// fine
		std::atomic<int> ai2(0);	// fine
		std::atomic<int> ai3 = 0;	// error!

	Of C++’s three ways to designate an initializing expression, only braces can be used everywhere.

Advantage of Braced initialization:
	1. prohibits implicit narrowing conversions
	2. immune to C++’s most vexing parse

	Braced initialization prohibits implicit narrowing conversions among built-in types.
		double x, y, z;
		int sum1{ x + y + z };	// error! sum of doubles may not be expressible as int
		int sum2(x + y + z);	// OK
		int sum3 = x + y + z;	// OK
		
	Braced initialization is immune to C++’s most vexing parse. 
	A side effect of C++’s rule that anything that can be parsed as a declaration must be interpreted as one, 
	the most vexing parse most frequently afflicts developers when they want to default-construct an object, 
	but inadvertently end up declaring a function instead.
		Widget w1(10);	// call Widget ctor with argument 10
		Widget w2();	// most vexing parse! declares a function named w2 that returns a Widget!

	Functions can’t be declared using braces for the parameter list,
	so default-constructing an object using braces doesn’t have this problem:
		Widget w3{};	// calls Widget ctor with no args

Drawbacks of Braced initialization:
	1. braced initializers is hijacked by std::initializer_list constructor if it’s present
	2. In case of template code it’s not possible to know which should be used
	
	In constructor calls, parentheses and braces have the same meaning as long as std::initializer_list parameters are not involved

	Strongly. If there’s any way for compilers to construe a call using a braced initializer to be 
	to a constructor taking a std::initializer_list, compilers will employ that interpretation
		class Widget {
			public:
			Widget(int i, bool b); // as before
			Widget(int i, double d); // as before
			Widget(std::initializer_list<long double> il); // added
		};

	Even what would normally be copy and move construction can be hijacked by std::initializer_list constructors

	Compilers’ determination to match braced initializers with constructors taking std::initializer_lists is so strong, 
	it prevails even if the best-match std::initializer_list constructor can’t be called.

	Only if there’s no way to convert the types of the arguments in a braced initializer 
	to the type in a std::initializer_list do compilers fall back on normal overload resolution.

	Suppose you use an empty set of braces to construct an object that supports 
	default construction and also supports std::initializer_list construction. 
	What do your empty braces mean? 
	If they mean “no arguments,” you get default construction, but 
	if they mean “empty std::initializer_list,” you get construction from a std::initializer_list with no elements.
	Empty braces mean no arguments, not an empty std::initializer_list.

	The difference with std::initializer_list constructor overloads is that 
	a std::initializer_list overload doesn’t just compete with other overloads, 
	it overshadows them to the point where the other overloads may hardly be considered.  
	So add such overloads only with great deliberation.

	There’s no consensus that either approach is better than the other, so my advice is to pick one and apply it consistently.

	In case of template code it’s not possible to know which should be used
		
Summary:

	• Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it’s immune to C++’s most vexing parse.
	• During constructor overload resolution, braced initializers are matched to std::initializer_list parameters if at all possible, even if other constructors offer seemingly better matches.
	• An example of where the choice between parentheses and braces can make a significant difference is creating a std::vector<numeric type> with two arguments.
	• Choosing between parentheses and braces for object creation inside templates can be challenging.	

**********/

#include <iostream>
#include <memory>
#include <atomic>
#include <vector>

class S {
    std::string name;

    public:
    S() { std::puts("S()"); }
    S(const std::string name) : name(name) {
         std::puts("S(const std::string name)"); 
    }

    S(const S & s) : name(s.name) {
        std::puts("S(const S & s)");
    }
    S& operator=(const S & s) { 
        
        std::puts("S& operator=(const S & s)");

        if(this == &s) {
            return *this;
        }
        name = s.name;
        return *this;
    }
    
};


class NonCopyable {
    int val;
    public:
    NonCopyable(const int val) : val(val) {}
    NonCopyable(const NonCopyable &)                = delete;
    NonCopyable& operator=(const NonCopyable &)     = delete;
};

class WithoutInitlist {
    int x, y;
    public:
    WithoutInitlist(const int x, const bool y) { 
        std::puts("WithoutInitlist(const int x, const bool y)");
    }
    WithoutInitlist(const int x, const double y) {
        std::puts("WithoutInitlist(const int x, const double y)");
    }
};

class WithInitlist {
    int x, y;
    public:
    WithInitlist() { std::puts("WithInitlist()"); }
    WithInitlist(const int x, const bool y) {
        std::puts("WithInitlist(const int x, const bool y)");
    }
    WithInitlist(const int x, const double y) {
        std::puts("WithInitlist(const int x, const double y)");
    }
    WithInitlist(const std::initializer_list<long double> ilist) {
        std::puts("(const std::initializer_list<long double> ilist)");
    }

    /*  CASE -2 Narrow conversion
    WithInitlist(const std::initializer_list<int> ilist) {
        std::puts("(const std::initializer_list<long double> ilist)");
    }
    */

    WithInitlist(const WithInitlist &) {
        std::puts("(const WithInitlist &)");
    }
    WithInitlist& operator=(const WithInitlist &) {
        std::puts("operator=(const WithInitlist &)");
        return *this;
    }

    WithInitlist(WithInitlist &&) {
        std::puts("(WithInitlist &&)");
    }
    WithInitlist& operator=(WithInitlist &&) {
        std::puts("operator=(WithInitlist &&)");
        return *this;
    }

    operator float() const {
        return static_cast<float>(x);
    }
};

class WithInitlistNoImplicitConversionPossible {
    int x, y;
    public:
    WithInitlistNoImplicitConversionPossible(const int x, const bool y) {
        std::puts("WithInitlistNoImplicitConversionPossible(const int x, const bool y)");
    }
    WithInitlistNoImplicitConversionPossible(const int x, const double y) {
        std::puts("WithInitlistNoImplicitConversionPossible(const int x, const double y)");
    }
    WithInitlistNoImplicitConversionPossible(const std::initializer_list<std::string> ilist) {
        std::puts("(const std::initializer_list<long double> ilist)");
    }

    WithInitlistNoImplicitConversionPossible(const WithInitlistNoImplicitConversionPossible &) {
        std::puts("(const WithInitlistNoImplicitConversionPossible &)");
    }
    WithInitlistNoImplicitConversionPossible& operator=(const WithInitlistNoImplicitConversionPossible &) {
        std::puts("operator=(const WithInitlistNoImplicitConversionPossible &)");
        return *this;
    }

    WithInitlistNoImplicitConversionPossible(WithInitlistNoImplicitConversionPossible &&) {
        std::puts("(WithInitlistNoImplicitConversionPossible &&)");
    }
    WithInitlistNoImplicitConversionPossible& operator=(WithInitlistNoImplicitConversionPossible &&) {
        std::puts("operator=(WithInitlistNoImplicitConversionPossible &&)");
        return *this;
    }

    operator float() const {
        return static_cast<float>(x);
    }
};

template<typename T, typename ... Args>
void display(Args ...args) {
    {   std::puts("Using paranthesis");
        T lval(std::forward<Args>(args)...); 

        for(const auto & elem : lval) {
            std::puts(std::to_string(elem).c_str());
        }       
    }

    {   std::puts("Using braces");
        T lval{std::forward<Args>(args)...}; 

        for(const auto & elem : lval) {
            std::puts(std::to_string(elem).c_str());
        }       
    }
    
}

int main() {

    {   std::puts("=== C++ initialization ===");
        int a = 5;
        int b{5};
        int c(5);
        int d = {5};

        S s1;           // default constructor
        S s2 = s1;      // copy constructor
        s1 = s2;        // copy aasignment
    }

    {   std::puts("=== C++11 uniform initialization ===");

        std::puts("prohibits implicit narrowing conversions");
        class G {
            //int x(0);   // CE error: expected identifier before numeric constant
            int y{0};
            int z = 0;
        };

        std::puts("uncopyable objects can not be initialized using “=”");
        std::unique_ptr<int>    lup1(new int{5});
        std::unique_ptr<int>    lup2{ new int{5}};
        //std::unique_ptr<int>    lup3 = new int{5};  // conversion from 'int*' to non-scalar type 'std::unique_ptr<int>' requested

        std::atomic<int>    a(4);
        std::atomic<int>    a2{4};
        //std::atomic<int>    a3 = 4; // error: use of deleted function 'std::atomic<int>::atomic(const std::atomic<int>&)'

        NonCopyable         nc1(7);
        NonCopyable         nc2{7};
        //NonCopyable         nc3 = 7;    // error: copying variable of type 'NonCopyable' invokes deleted constructor
    }

    {   std::puts("=== Advantage of Braced initialization ===");
        double d1 = 10.3;
        double d2 = 31.6;
        double d3 = 7.12;

        std::puts("prohibits implicit narrowing conversions");
        int res1(d1 + d2 + d3);     // warning: implicit conversion turns floating-point number into integer: 'double' to 'int' [-Wfloat-conversion]
        //int res2{d1 + d2 + d3};   // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
        int res3 = d1 + d2 + d3;    // warning: implicit conversion turns floating-point number into integer: 'double' to 'int' [-Wfloat-conversion]

        std::puts("immune to C++’s most vexing parse");
        S s1;
        S s2("sample string");
        S s3{"sample string"};

        S s4(); // warning: empty parentheses interpreted as a function declaration [-Wvexing-parse]
        S s5{};
    }

    {   std::puts("=== Drawbacks of Braced initialization ===");
        
        {   std::puts("constructor without braces calls normal constructor");
            WithoutInitlist w11(10, true);
            WithoutInitlist w12(10, 35.68);

            WithInitlist    w21(10, true);
            WithInitlist    w22(10, 35.68);
        }
        std::puts("");
        
        {   std::puts("braced initializers is hijacked by std::initializer_list");

            WithoutInitlist w11{10, true};
            WithoutInitlist w12{10, 35.68};

            WithInitlist    w21{10, true};
            WithInitlist    w22{10, 35.68};
            //WithInitlist    w22{10, 35.68};     // CASE-2 error: narrowing conversion of '3.568e+1' from 'double' to 'int'
        }
        std::puts("");
        
        {   std::puts("copy and move construction can be hijacked by std::initializer_list constructors");

            WithInitlist    w1{10, true};
            WithInitlist    w2{10, 35.68};
            //WithInitlist    w2{10, 35.68};  // CASE -2 error: narrowing conversion of '3.568e+1' from 'double' to 'int'

            WithInitlist    wc1(w1);
            WithInitlist    wc2{w2};    // calls init list const.

            WithInitlist    wm1(std::move(w1));
            WithInitlist    wm2{std::move(w2)}; // calls init list const.
        }
        std::puts("");

        {   std::puts("Non initializer_list constructor is called when implicit conversion is not possible");
            WithInitlist    w3{10, true};
            WithInitlist    w4{10, 35.68};

            WithInitlistNoImplicitConversionPossible    wnic3{10, true};    // calls normal const.
            WithInitlistNoImplicitConversionPossible    wnic4{10, 35.68};   // calls normal const.
        }
        std::puts("");

        {   std::puts("call initializer_list constructor with 0 argument");
            WithInitlist w1;    // default constructor
            WithInitlist w2{};  // default constructor
            WithInitlist w3();  // most vex parse

            WithInitlist w4({});    // initializer_list constructor 
            WithInitlist w5{{}};    // initializer_list constructor 

        }
        std::puts("");

        std::puts("In case of template code it’s not possible to know which should be used");
        {
            display<std::vector<int>>(5, 20);
        }

    }

    return 0; 
}

/*****
    END OF FILE
**********/


