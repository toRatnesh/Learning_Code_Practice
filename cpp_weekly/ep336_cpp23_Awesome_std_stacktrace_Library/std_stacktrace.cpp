/******************
  This example demonstrates about C++23 Stacktrace library

  For more info visit:
	https://en.cppreference.com/w/cpp/utility/basic_stacktrace
	https://www.youtube.com/watch?v=9IcxniCxKlQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=339
 ********************/

#include <iostream>
#include <stacktrace>

struct Base {
	virtual void display() { 
		std::clog << "inside Base()\n"; 
		auto trace = std::stacktrace::current();
		std::clog << std::to_string(trace) << '\n';
	}
};
struct Derived : public Base {
	void display() { 
		std::clog << "inside Derived()\n"; 
		auto trace = std::stacktrace::current();
		std::clog << std::to_string(trace) << '\n';
	}
};

inline void inline_fun() {
	auto trace = std::stacktrace::current();
	std::clog << std::to_string(trace) << '\n';
}

void fun() {
	auto trace = std::stacktrace::current();
	std::clog << std::to_string(trace) << '\n';
}

int main() {
	auto trace = std::stacktrace::current();
	std::clog << std::to_string(trace) << '\n';

	fun();
	inline_fun();

	Base b1;
	b1.display();

	Derived d1;
	d1.display();

	Base * bptr = new Derived;
	bptr->display();

	return 0;
}

/******
  END OF FILE
 *******/
