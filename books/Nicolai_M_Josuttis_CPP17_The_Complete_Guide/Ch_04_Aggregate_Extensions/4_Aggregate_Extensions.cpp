/**************

References:
	C++17 - The Complete Guide | Nicolai M. Josuttis

Aggregate
    Aggregates are either arrays or simple, C-like classes that have no user-provided constructors, no private or protected non-static data members, no virtual functions, and before C++17 no base classes.

Aggregate Extensions
    C++ aggregate initialization allows the initialization of an aggregate from multiple values with curly braces
    Since C++17, aggregates can have base classes, so that for such structures being derived from other classes/structures list initialization is allowed

4.1 Motivation for Extended Aggregate Initialization
    Without this feature, deriving a structure from another disabled aggregate initialization, so that you had to define a constructor

4.2 Using Extended Aggregate Initialization
    You can skip initial values. In that case the elements are zero initialized (calling the default constructor or initializing fundamental data types with 0, false, or nullptr).
    You can also derive aggregates from non-aggregate classes.
    You can even derive aggregates from multiple base classes and/or aggregates.

4.3 Definition of Aggregates
    since C++17 an aggregate is defined as
        • either an array
        • or a class type (class, struct, or union) with:
            – no user-declared or explicit constructor
            – no constructor inherited by a using declaration
            – no private or protected non-static data members
            – no virtual functions
            – no virtual, private, or protected base classes

    Use C++17 type trait is_aggregate<> to test, whether a type is an aggregate

4.4 Backward Incompatibilities
    Adding Derived as friend to base will fail to compile, Because since C++17, Derived is an aggregate.


***********/

#include <iostream>
#include <string>
#include <complex>
#include <type_traits>

struct BaseWithSingleMember {
    std::string b11;
};

struct BaseWithMultipleMember {
    std::string b21;
    std::string b22;
};

struct DerivedSS : public BaseWithSingleMember {
    int d11;
};

struct DerivedSM : public BaseWithMultipleMember {
    int d21;
};

struct DerivedMS : public BaseWithSingleMember {
    int d31;
    int d32;
};

struct DerivedMM : public BaseWithMultipleMember {
    int d41;
    int d42;
};

template<typename T>
struct DerivedFromNonAggregate : std::string, std::complex<T> {
	std::string data;
};

struct Derived;
struct Base { 
        friend struct Derived;
    private:
        Base() { }
};
struct Derived : Base {
};

int main() {

    BaseWithSingleMember	b1{"base with single member"};
	std::clog << "b1.b11: " << b1.b11 << '\n';
	BaseWithMultipleMember	b2{"base with multiple member 1", "base with multiple member 2"};
	std::clog << "b2.b21: " << b2.b21 << ", b2.b22: " << b2.b22 << '\n';
	
	DerivedSS d11{{"base with single member"}, 11};
	std::clog << "d11.b11: " << d11.b11 << ", d11.d11: " << d11.d11 << '\n';
    DerivedSS d12{"base with single member", 12};
	std::clog << "d12.b11: " << d12.b11 << ", d12.d11: " << d12.d11 << '\n';
	
	DerivedSM d21{{"base with multiple member 1", "base with multiple member 2"}, 21};
	std::clog << "d21.b21: " << d21.b21 << ", d21.b22: " << d21.b22 << ", d21.d21: " << d21.d21 << '\n';
	DerivedSM d22{"base with multiple member 1", "base with multiple member 2", 22};
	std::clog << "d22.b21: " << d22.b21 << ", d22.b22: " << d22.b22 << ", d22.d21: " << d22.d21 << '\n';

	DerivedMS d31{{"base with single member"}, 31, 41};
	std::clog << "d31.b11: " << d31.b11 << ", d31.d31: " << d31.d31 << ", d31.d32: " << d31.d32 << '\n';
	DerivedMS d32{"base with single member", 32, 42};
	std::clog << "d32.b11: " << d32.b11 << ", d32.d31: " << d32.d31 << ", d32.d32: " << d32.d32 << '\n';

	DerivedMM d41{{"base with multiple member 1", "base with multiple member 2"}, 41, 51};
	std::clog << "d41.b21: " << d41.b21 << ", d41.b22: " << d41.b22 << ", d41.d41: " << d41.d41 << ", d41.d42 " << d41.d42 << '\n';
	DerivedMM d42{"base with multiple member 1", "base with multiple member 2", 42, 52};
	std::clog << "d42.b21: " << d42.b21 << ", d42.b22: " << d42.b22 << ", d42.d41: " << d42.d41 << ", d42.d42 " << d42.d42 << '\n';
	
	DerivedMM dmm1{};
	std::clog << "dmm1.b21: " << dmm1.b21 << ", dmm1.b22: " << dmm1.b22 << ", dmm1.d41: " << dmm1.d41 << ", dmm1.d42 " << dmm1.d42 << '\n';
    DerivedMM dmm2{{}, 5, 6};
	std::clog << "dmm2.b21: " << dmm2.b21 << ", dmm2.b22: " << dmm2.b22 << ", dmm2.d41: " << dmm2.d41 << ", dmm2.d42 " << dmm2.d42 << '\n';

    DerivedFromNonAggregate<double> dnonag{{"hello"}, {4.5,6.7}, "world"};
    std::clog << "std::is_aggregate_v<decltype(dnonag)> " << std::is_aggregate_v<decltype(dnonag)> << '\n';

    //Derived d1{}; // error: 'Base::Base()' is private within this context
    Derived d2;     // still OK (but might not initialize)

    return 0;
}

/***************
    END OF FILE
****************/

