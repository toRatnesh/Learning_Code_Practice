/*************
 *	This example demonstrates the use of explicit constrcutor which prevents constructor from working as a converting constructor.
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/converting_constructor
 *
 * **************/

#include <iostream>

struct A {
	A() { std::puts("A()"); }         // converting constructor (since C++11)  
	A(int) { std::puts("A(int)"); }      // converting constructor
	A(int, int) { std::puts("A(int, int)"); } // converting constructor (since C++11)
};

struct B {
	explicit B() { std::puts("B()"); }
	explicit B(int) { std::puts("B(int)"); }
	explicit B(int, int) { std::puts("B(int, int)"); }
};

void fun_a(const A & param) {
	std::puts("fun_a");
}

void fun_b(const B & param) {
	std::puts("fun_b");
}

int main() {
	A a1 = 1;      // OK: copy-initialization selects A::A(int)
	A a2(2);       // OK: direct-initialization selects A::A(int)
	A a3{4, 5};    // OK: direct-list-initialization selects A::A(int, int)
	A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
	A a5 = (A)1;   // OK: explicit cast performs static_cast, direct-initialization

	//B b1 = 1;      // error: copy-initialization does not consider B::B(int)
	B b2(2);       // OK: direct-initialization selects B::B(int)
	B b3{4, 5};    // OK: direct-list-initialization selects B::B(int, int)
	//B b4 = {4, 5}; // error: copy-list-initialization selected an explicit constructor
	//        B::B(int, int)
	B b5 = (B)1;   // OK: explicit cast performs static_cast, direct-initialization
	B b6;          // OK, default-initialization
	B b7{};        // OK, direct-list-initialization
	//B b8 = {};     // error: copy-list-initialization selected an explicit constructor
	//        B::B()

	fun_a(1);       // OK: copy-initialization selects A::A(int)
	//fun_b(1);     // error: copy-initialization does not consider B::B(int)
	fun_a({3,5});   // OK: copy-list-initialization selects A::A(int, int)
	//fun_b({3,5}); // error: copy-list-initialization selected an explicit constructor
	//        B::B(int, int)

	return 0;
}

/******
 *	END OF FILE
 * ******/
