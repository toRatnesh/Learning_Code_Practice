/*****

References

    Effective Modern C++ | Scott Meyers
    https://en.cppreference.com/w/cpp/language/rule_of_three
    https://blog.feabhas.com/2015/11/becoming-a-rule-of-zero-hero/
    https://www.foonathan.net/2019/02/special-member-functions/
    https://mariusbancila.ro/blog/2018/07/26/cpp-special-member-function-rules/

Item 17: Understand special member function generation

Special member function
    the ones that C++ is willing to generate on its own
    generated only if they’re needed

C++98
	default constructor,
	destructor,
	copy constructor,
	copy assignment operator
	
	
A default constructor is generated only if the class declares no constructors at all.

Generated special member functions are implicitly public and inline, 
and they’re nonvirtual unless the function in question is a destructor in a derived class 
inheriting from a base class with a virtual destructor.

C++11
	default constructor,
	destructor,
	copy constructor,
	copy assignment operator,
	move constructor,
	move assignment operator

Move operations
	move constructor move-constructs (move assignment operator move-assigns) 
	each nonstatic data member of the class from the corresponding member of its parameter rhs
	
	same happens also for base class part (if there are any)
	
	“Memberwise moves” are, in reality, more like memberwise move requests, because types that aren’t move-enabled 
	(i.e., that offer no special support for move operations, e.g., most C++98 legacy classes) 
	will be “moved” via their copy operations.

Move operations generation
	As is the case with the copy operations, the move operations aren’t generated if you declare them yourself. 
	However, the precise conditions under which they are generated differ a bit from those for the copy operations.

	The two copy operations are independent: declaring one doesn’t prevent compilers from generating the other.
	
	The two move operations are not independent. If you declare either, that prevents compilers from generating the other.
	
	if you declare, say, a move constructor for your class, you’re indicating that there’s something about 
	how move construction should be implemented that’s different from the default memberwise move that compilers would generate. 
	And if there’s something wrong with memberwise move construction, there’d probably be something wrong with 
	memberwise move assignment, too. So declaring a move constructor prevents a move assignment operator from being generated, 
	and declaring a move assignment operator prevents compilers from generating a move constructor.
	
	move operations won’t be generated for any class that explicitly declares a copy operation
	This goes in the other direction, too. 
	Declaring a move operation (construction or assignment) in a class causes compilers to disable the copy operations.
	(The copy operations are disabled by deleting them).
	
	Rule of Three
		if you declare any of a copy constructor, copy assignment operator, or destructor, you should declare all three

	So move operations are generated for classes (when needed) only if these three things are true:
		• No copy operations are declared in the class.
		• No move operations are declared in the class.
		• No destructor is declared in the class.
		
	C++11 deprecates the automatic generation of copy operations for classes declaring copy operations or a destructor.
	
C++11 rules governing the special member functions are:

	Default constructor: 
		Same rules as C++98. Generated only if the class contains no user-declared constructors

	Destructor:
		Same rules as C++98; virtual only if a base class destructor is virtual.
		Difference is that destructors are noexcept by default. 
		
	Copy constructor: 
		Same runtime behavior as C++98: memberwise copy construction of non-static data members.
		Deleted if the class declares a move operation.
		Generation of this function in a class with a user-declared copy assignment operator or destructor is deprecated.
		
	Copy assignment operator:
		Same runtime behavior as C++98: memberwise copy assignment of non-static data members.
		Deleted if the class declares a move operation.
		Generation of this function in a class with a user-declared copy constructor or destructor is deprecated.
		
	Move constructor and move assignment operator:
		Each performs memberwise moving of non-static data members.
		Generated only if the class contains no userdeclared copy operations, move operations, or destructor.

Rule of Three
	if you declare any of a copy constructor, copy assignment operator, or destructor, you should declare all three

Rule of five
	Because the presence of a user-defined (or = default or = delete declared) destructor, 
	copy-constructor, or copy-assignment operator prevents implicit definition 
	of the move constructor and the move assignment operator, 
	any class for which move semantics are desirable, has to declare all five special member functions.

Template and Special member functions
	Note that there’s nothing in the rules about the existence of a member function template 
	preventing compilers from generating the special member functions.
	That means that if Widget looks like this,

		class Widget {
			…
			
			template<typename T> // construct Widget
			Widget(const T& rhs); // from anything
			
			template<typename T> // assign Widget
			Widget& operator=(const T& rhs); // from anything
			
			…
		};

	compilers will still generate copy and move operations for Widget


Summary
	•	The special member functions are those compilers may generate on their own: 
		default constructor, destructor, copy operations, and move operations.
	•	Move operations are generated only for classes lacking explicitly declared 
		move operations, copy operations, and a destructor.
	•	The copy constructor is generated only for classes lacking an explicitly declared copy constructor, 
		and it’s deleted if a move operation is declared. 
		The copy assignment operator is generated only for classes lacking an explicitly declared copy assignment operator, 
		and it’s deleted if a move operation is declared.
		Generation of the copy operations in classes with an explicitly declared destructor is deprecated.
	•	Member function templates never suppress generation of special member functions.



                                    compiler implicitly declares
    ==============================================================================================================
    |			|default	|	destructor|  copy      |  copy       |   move      | move        |
    |			|constructor	|             	  | constructor| assignment  | constructor | assignment  |
    ==============================================================================================================
    |	None		| defaulted 	| defaulted   	  | defaulted  | defaulted   |  defaulted  | defaulted   |
    |			|           	|             	  |            |             |             |             |
    --------------------------------------------------------------------------------------------------------------
    |	Any		|    X      	| defaulted   	  | defaulted  | defaulted   |  defaulted  | defaulted   |
    |Constructor	|           	|             	  |            |             |             |             |
    --------------------------------------------------------------------------------------------------------------
    | default		|    O      	| defaulted   	  | defaulted  | defaulted   |  defaulted  | defaulted   |
    |Constructor	|           	|             	  |            |             |             |             |
    --------------------------------------------------------------------------------------------------------------
    |destructor		| defaulted 	| 	O	  | defaulted  | defaulted   |	   X  	   |	X	 |
    |			|           	|             	  |(deprecated)|(deprecated) |             |             |
    --------------------------------------------------------------------------------------------------------------
    | Copy		| 	  X	| defaulted   	  | 	O      | defaulted   |	   X  	   | 	X	 |
    |Constructor	|           	|             	  |            |(deprecated) |             |             |
    --------------------------------------------------------------------------------------------------------------
    | Copy		| defaulted 	| defaulted   	  | defaulted  | 	O    |     X	   | 	X	 |
    |assignment 	|           	|             	  |(deprecated)|	     |             |             |
    --------------------------------------------------------------------------------------------------------------
    | move		| 	  X	| defaulted   	  | deleted    | deleted     |	   O  	   | 	X	 |
    |Constructor	|         	|             	  |	       |	     |             |             |
    --------------------------------------------------------------------------------------------------------------
    | move		| defaulted 	| defaulted   	  | deleted    | deleted     |     X	   | 	O	 |
    |assignment 	|           	|             	  |	       |	     |             |             |
    ==============================================================================================================

    X - Not declared

**********/

#include <iostream>


class St {
    int     val;
    public:
    
    ~St()   { std::puts("~St()"); }
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

};

class OnlyDestructor {
    St      mst;
    public:
    ~OnlyDestructor() { std::puts("~OnlyDestructor()"); }
};

class OnlyCopyConstructor {
    St      mst;
    public:
    OnlyCopyConstructor(const OnlyCopyConstructor & other) :mst(other.mst) {
        std::puts("OnlyCopyConstructor(const OnlyCopyConstructor & other)");
    }  
};

class OnlyCopyAssignment {
    St      mst;
    public:

    OnlyCopyAssignment& operator=(const OnlyCopyAssignment & other) {
        std::puts("operator=(const OnlyCopyAssignment & other)");

        if(this != &other) {
            mst = other.mst;
        }
        return *this;
    }    
};

class OnlyMoveConstructor {
    St      mst;
    public:
    OnlyMoveConstructor(OnlyMoveConstructor && other) :mst(std::move(other.mst)) {
        std::puts("OnlyMoveConstructor(OnlyMoveConstructor && other)");
    }  
};

class OnlyMoveAssignment {
    St      mst;
    public:

    OnlyMoveAssignment& operator=(OnlyMoveAssignment && other) {
        std::puts("operator=(OnlyMoveAssignment && other)");

        if(this != &other) {
            mst = std::move(other.mst);
        }
        return *this;
    }    
};

class AllAvailable {
    St      mst;
    public:
    ~AllAvailable() = default;
    AllAvailable()  = default;

    AllAvailable(const AllAvailable &)              = default;
    AllAvailable& operator=(const AllAvailable &)   = default;

    AllAvailable(AllAvailable &&)                   = default;
    AllAvailable& operator=(AllAvailable &&)        = default;
};



int main() {

    {   std::puts("=== using class with only destructor ===");
        OnlyDestructor  od1;
        OnlyDestructor  od2{od1};
        od2 = od1;

        OnlyDestructor  od3{std::move(od1)};    // move operation by copy operation
        od3 = std::move(od2);                   // move operation by copy operation
    }

    
    {   std::puts("\n=== using class with only copy constructor ===");
        // CE // error: no matching function for call to 'OnlyCopyConstructor::OnlyCopyConstructor()'
        //OnlyCopyConstructor  od1;
    }


    {   std::puts("\n=== using class with only copy assignment ===");
        OnlyCopyAssignment  o1;

        // warning: implicitly-declared 'OnlyCopyAssignment::OnlyCopyAssignment(const OnlyCopyAssignment&)' is deprecated
        OnlyCopyAssignment  o2{o1};
        o2 = o1;

        // warning: implicitly-declared 'OnlyCopyAssignment::OnlyCopyAssignment(const OnlyCopyAssignment&)' is deprecated
        OnlyCopyAssignment  o3{std::move(o1)};      // move operation by copy operation
        o3 = std::move(o2);                         // move operation by copy operation
    }

    {   std::puts("\n=== using class with only move constructor ===");
        // CE error: no matching function for call to 'OnlyMoveConstructor::OnlyMoveConstructor()'
        // OnlyMoveConstructor o1;
    }    

    {   std::puts("\n=== using class with only move assignment ===");
        OnlyMoveAssignment  o1;
        OnlyMoveAssignment  o2;

        // CE error: use of deleted function 'OnlyMoveAssignment::OnlyMoveAssignment(const OnlyMoveAssignment&)'
        //OnlyMoveAssignment  o2{o1};
        // CE error: use of deleted function 'OnlyMoveAssignment& OnlyMoveAssignment::operator=(const OnlyMoveAssignment&)'
        //o2 = o1;

        // CE error: use of deleted function 'OnlyMoveAssignment::OnlyMoveAssignment(const OnlyMoveAssignment&)'
        // OnlyMoveAssignment  o3{std::move(o1)};
        o2 = std::move(o1);                   
    }

    {   std::puts("\n=== using class with all special member functions ===");
        AllAvailable  o1;
        AllAvailable  o2{o1};
        o2 = o1;

        AllAvailable  o3{std::move(o1)};
        o3 = std::move(o2);
    }

    return 0;
}

/*****
    END OF FILE
**********/


