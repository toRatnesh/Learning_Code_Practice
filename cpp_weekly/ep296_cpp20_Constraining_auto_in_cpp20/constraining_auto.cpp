/****************
  This example demonstrates the use of constraints and concepts of C++20 to restrict auto as
  return type
  parameter type 
  object type

  For more info visit:
Tutorial:   https://www.youtube.com/watch?v=A8nNjpaiP5M&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=297

 ******************/

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

	return 0;
}

auto fun() {
	return 1;
}

/********
  END OF FILE
 *******/
