/**************
  This example demonstrates about C++ std::function like implementation

  For more info visit:
	https://www.youtube.com/watch?v=xJSKk_q25oQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=334
	https://github.com/NemesisWasAlienToo/CoreKit/blob/main/Library/Function.hpp

 ***************/

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>

namespace nonstd {
	template <typename T>
		class function;

	template <typename Ret, typename... Args>
		class function<Ret(Args...)> {
			Ret (*m_fp)(Args...);

			struct callable_interface {
				virtual Ret call(Args... args) = 0;
				virtual ~callable_interface() = default;
				// finish rule of 5
				// virtual clone

			};
			std::unique_ptr<callable_interface> callable;

			template <typename callable_t>
				struct callable_impl : public callable_interface {
					callable_t callable;

					callable_impl(callable_t callable) : callable(callable) {}

					// use std::invoke
					Ret call(Args... args) { return callable(args...); }
				};

			public:
			function(Ret (*fp)(Args...))
				: callable{std::make_unique<callable_impl<Ret (*)(Args...)>>(fp)} {}
			// add a plethora of other constructors


			Ret operator()(Args... args) { return callable->call(args...); }
			// copy constructor
		};
}  // namespace nonstd

struct S {
	int m = 5;

	public:
	int memberFun(int arg) { return arg + m; }

	static int staticMemberFun(int arg) { return arg * 2; }
};

int main() {
	auto alambda = [](const int x, const int y) { return x + y; };
	static_assert(5 == alambda(2, 3));
	nonstd::function<int(int, int)> func{alambda};
	assert(5 == func(2, 3));

	const int multiply_by_this = 7;
	auto alambda2 = [multiply_by_this](const int val) {
		return val * multiply_by_this;
	};
	static_assert(56 == alambda2(8));
	std::function<int(int)> func2{alambda2};
	assert(56 == func2(8));

	// For static member functions (it's like free fucntions)
	func2 = S::staticMemberFun;
	assert(8 == func2(4));

	// For member functions
	std::function<int(S&, int)> funcm = &S::memberFun;
	int (S::*fpm)(int) = nullptr;
	fpm = &S::memberFun;
	S sobj;
	assert(10 == (sobj.*fpm)(5));
	assert(8 == funcm(sobj, 3));

	return 0;
}

/********
  END OF FILE
 *******/
