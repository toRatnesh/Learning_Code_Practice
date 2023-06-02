/*********
    This example demonstrates about how constructor and destructor are not real function
    but in actual they are conversion operators which initializes object of the class from given arguemnts

    constructors are not real functions they donot actuaaly exist
    they are conversion operator from a set of parameters to a particular type

    For more info visit:
    episode: https://www.youtube.com/watch?v=afDB4kpYnzY

***************/

#include <iostream>
#include <string>

class S {

    public:
    ~S() { std::cout << "~S()\n"; }
    S() { std::cout << "S()\n"; }

    template<int>
    S() { std::cout << "S<int>()\n"; }
    
    template <typename T>
    S([[maybe_unused]] T parm) { std::cout << "S<T>()\n"; } 

    int get()       { std::cout << "get()\n"; return 0; }
    int getOther()  { std::cout << "getOther()\n"; return 0; }
};

class C {
    public:
    ~C() { std::cout << "~C()\n"; }
    C([[maybe_unused]] int parm) { std::cout << "C(int)\n"; }
};

int main() {

    {
        std::cout << "=== member function pointer ===\n";
        {
        using mem_funcp = int (S::*)();

        S s;

        mem_funcp mfp_get = &S::get;
        (s.*mfp_get)();

        mfp_get = &S::getOther;
        (s.*mfp_get)();   

        std::cout << "=== Explicit call to destructor is undefined behavior(UB) ===\n";
        // explicit call to destrutor is UB
        std::cout << "Calling s.~S() is UB\n";
        s.~S();
        }

        std::cout << "=== Explcit call to construtor is not allowed ===\n";
        // explicit call to constrcutor is not allowed
        //S::S(); // CE error: cannot call constructor 'S::S' directly
        std::cout << "Calling S::S() is not allowed\n";

        /*
        member function pointer to constructor and destructor is not allowed
        becasue they do not specify any return value
        */
        std::cout << "\n=== Member function pointer to constructor and destructor is not allowed ===\n";
        using mem_funcp_des = void (S::*)();
        //mem_funcp_des desp = &S::~S;  // CE error: taking address of destructor 'S::~S()'
        //mem_funcp_des conp = &S::S;   // CE error: taking address of constructor 'constexpr S::S(const S&)'
    }

    {
        std::cout << "\n=== templated construtor ===\n";
        
        // there is no syntax like this
        //S s<int>();
        //S s::S<int>();
        //S::S<int>();

        // templated constructor, object cration uses memeber type template deduction
        S s(42);
        S(42);
    }

    {
        std::cout << "\n=== explicit cast ===\n";
        {C(26);}
        {(C)26;}                // explicit constrcution from 42 to C
        {(C)(2, 3);}            // comma operator is coming into effect
        {static_cast<C>(36);}   // explicit cast 
    }

    {
        std::cout << "\n=== explicit cast and reinterpret cast ===\n";
        // this is not reinterpret cast, this is explicit conversion
        [[maybe_unused]] auto s1 = (std::string)"sample string";
        std::string str = R"(sample string)";
        std::cout << "explicit cast: " << "(std::string)\"sample string\"" << '\n';

        // this is reinterpret cast
        [[maybe_unused]] auto s2 = (std::string *)"sample string";
        std::cout << "reinterpret cast: " << "(std::string *)\"sample string\"" << '\n';
    }

    return 0;
}

/*********
    END OF FILE
***************/

