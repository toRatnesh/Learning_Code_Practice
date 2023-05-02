/**********

    This example demonstrates about C++ unions
    For more info visit
    episode https://www.youtube.com/watch?v=Lu1WsdQOi0E
    https://en.cppreference.com/w/cpp/language/union

    Few points about union:
    *   union can be anonymous (unnamed)
    *   only one member can be active at a time
    *   only active member can be accessed, accessing other members is undefined behavior
    *   there is no default active member 
    *   union may be used for delay initializing an object
    *   union can have constructor and destructor in C++11
    *   union destrcutor is impossible to get right because there is no way to check wheter member was initialized or not
    *   union support regular member funciton
    *   need manual logic to keep track of active member
    *   Proposal to check active member https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2641r1.html

*************/

#include <string>

consteval auto get_union_val() {
    // anonymous union
    union {
        int     ival;
        float   fval;
    };

    fval = 2.5f;
    ival = 10;

    //return fval; // CE error: accessing 'get_union_val()::<unnamed union>::fval' member instead of initialized 'get_union_val()::<unnamed union>::ival' member in constant expression
    return ival;
}

consteval auto get_union_val_02() {
    union U {
        double  dval;
        int     ival;
    };

    // size of union is equal to size of its biggest member
    static_assert(sizeof(U) == 8);

    U u;

    // can not access uninitialized member
    //return u.dval;  // CE error: accessing uninitialized member 'get_union_val_02()::U::dval'

    u.dval = 2.5;
    u.ival = 10;

    //return u.dval;  // CE error: accessing 'get_union_val_02()::U::dval' member instead of initialized 'get_union_val_02()::U::ival' member in constant expression
    return u.ival;
}

consteval auto get_union_val_03() {
    union U {
        constexpr U()   { };
        constexpr ~U()  { 
            mstr.std::string::~string();    // destructor for mstr, results in UB if mstr is not initialized
        };
        std::string     mstr;   // member with non-trivial object
    };

    /*  Error for non-trivial object WITHOUT USER DEFINED CONSTRUCTOR
    U u;    

    <source>:46:7: error: use of deleted function 'get_union_val_03()::U::U()'
    46 |     U u;
       |       ^
    <source>:43:11: note: 'get_union_val_03()::U::U()' is implicitly deleted because the default definition would be ill-formed:
    43 |     union U {
       |           ^
    <source>:44:21: error: union member 'get_union_val_03()::U::mstr' with non-trivial 'constexpr std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]'
    44 |         std::string mstr;   // member with non-trivial constructor
       | 
    */

    U u;
    static_assert(sizeof(u.mstr.size() == 0));

    //u.mstr = std::string("this is assignment not constrution");
    //new (&u.mstr) std::string("dynamic construction not allowed in constexpr");

    std::construct_at(&u.mstr, "construct using C++20 construct_at");
    //static_assert(34 == u.mstr.size());

    return u.mstr.size();
}

consteval auto get_union_val_04() {
    union U {
        int     ival;
        float   fval;

        constexpr U()           : ival{23}   { };
        constexpr U(float fval) : fval{fval} { };
        constexpr ~U() { };

        constexpr U & operator=(int val) {
            ival = val;
            return *this;
        }

        constexpr int to_int() const {
            return ival;
        }

    };

    constexpr U u1;
    static_assert(23 == u1.ival);
    static_assert(23 == u1.to_int());

    constexpr U u2{13.93f};
    static_assert(13.93f == u2.fval);

    U u3{3.2f};
    u3 = 63;
    //static_assert(63 == u3.ival);

    return u1.ival;
}


template<typename T>
class Soptional {
    union Data {
        T data;

        constexpr Data() {}
        constexpr ~Data() {}
        constexpr Data() requires (std::is_trivially_destructible_v<T>) = default;
    };
    bool is_active = false;
    Data data;

    public:
    constexpr Soptional() { };
    constexpr ~Soptional() requires (std::is_trivially_destructible_v<T>) = default;

    constexpr ~Soptional() {
        if(is_active) {
            std::destroy_at(&data.data);
        }
    }

    constexpr Soptional & operator=(const T & new_data) {
        if(is_active) {
            data.data = new_data;
        } else {
            std::construct_at(&data.data, new_data);
            is_active = true;
        }
        return *this;
    }

    constexpr const T & get() const {
        return data.data;
    }

};

consteval auto useSoptional() {
    Soptional<std::string> obj;
    Soptional<std::string> obj2;
    obj2 = {"simplified optional"};
    return obj2.get().size();
}

int main() {
    {
        [[maybe_unused]] constexpr auto uval = get_union_val();
        static_assert(10 == uval);
    }

    {
        [[maybe_unused]] constexpr auto uval = get_union_val_02();
        static_assert(10 == uval);
    }    
    
    {
        [[maybe_unused]] constexpr auto uval = get_union_val_03();
        static_assert(34 == uval);
    }

    {
        [[maybe_unused]] constexpr auto uval = get_union_val_04();
        static_assert(23 == uval);
    }

    {
        [[maybe_unused]] constexpr auto uval = useSoptional();
        static_assert(19 == uval);
    }

    {
        union U {
            int x;
            float y;
        };
        
        // Reference https://eel.is/c++draft/dcl.init.aggr#20
        // https://twitter.com/shafikyaghmour/status/1648027480492740609
        // following is ill-formed
        //U u{.x = 5, .y = 2.5f};  // Initialize x and then override and initialize y
        // CE error: too many initializers for 'main()::U'
    }
    return 0;
}

/********
    END OF FILE
*************/




