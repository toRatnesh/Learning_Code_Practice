/****************
  This example demonstrates the use of constraints and concepts of C++20 to restrict auto as
  return type
  parameter type
  object type

  For more info visit:
Tutorial:   https://www.youtube.com/watch?v=A8nNjpaiP5M&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=297

 ******************/

#include <iostream>
#include <concepts>
#include <cmath>
#include <memory>

auto fun();
auto fun2() {
	return 2;
}

std::integral auto fun3() {
	return 3;
}

std::floating_point auto fun4(std::integral auto val) {
	return std::sqrt(val);
}

int * fun5() {
	static int val = 5;
	return &val;
}

template <class T>
concept not_pointer = not(std::is_pointer_v<T>);


struct OtherClass {
	void display() const {
		std::puts("OtherClass");
	}
};

struct Base {
	virtual void display() const {
		std::puts("Base");
	}
};

struct D1 : Base {
	void display() const {
		std::puts("D1");
	}
};

struct D2 : Base {
	void display() const {
		std::puts("D2");
	}
};

template<class Derived >
concept Base_t = std::is_base_of_v<Base, Derived>;
auto display(Base_t auto const& b) { // display will only work for objct of Base and it's derived classes
	b.display();
}

auto display2(auto const& c) { // display2 will work for any class object which implements display() member function
	c.display();
}

int main() {
	[[maybe_unused]] auto lval1 = fun();    // error because type of lval1 cannot be deduced
	//because fun is callled before its definition and fun's return type is not yet deduced

	[[maybe_unused]] auto lval2 = fun2();

	[[maybe_unused]] auto lval3 = fun3();
	[[maybe_unused]] float fval = fun3(); // warning for conversion from int to float
	[[maybe_unused]] std::floating_point auto fval2 = fun3(); // error fval2 only accpets floating point

	[[maybe_unused]] auto lsqrt_val = fun4(5);
	[[maybe_unused]] std::floating_point auto lsqrt_val2 = fun4(5);
	[[maybe_unused]] auto lsqrt_val3 = fun4(11.3);    // error becasue fun4 paramter is integral type

	[[maybe_unused]] auto lret51 = fun5();
	[[maybe_unused]] auto * lret52 = fun5();
	[[maybe_unused]] not_pointer auto lret53 = fun5();  // error because lret53 doesnot accept pointer


	Base b;
	display(b);

	D1 d1;
	display(d1);

	D2 d2;
	display(d2);

	Base * bptr = new D1;
	display(*bptr);

	OtherClass oc;
	//display(oc);

	//display(1);

	display2(b);
	display2(d1);
	display2(d2);
	display2(*bptr);
	display2(oc);
	//display2(1);



	return 0;
}

auto fun() {
	return 1;
}

/********
  END OF FILE
 *******/

