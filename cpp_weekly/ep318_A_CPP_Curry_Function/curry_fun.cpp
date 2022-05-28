/**********************
  In this episode Jason talks about a C++ curry function which
  returns a new function with N parameters bound
  executes the fcuntion 

  For more info visit:
https://www.youtube.com/watch?v=15U4qutsPGk&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=319

 **********************/

#include <cassert>

namespace myns {

	int add(int a, int b, int c, int d) {
		return (a+b+c+d);
	}

	/*
	   template<typename Callable, typename ... Params>
	   auto curry_fun(Callable callable, Params ... bind_params) {

	   auto fun = [callable, bind_params...](auto ... passed_params) {
	   return callable(bind_params..., passed_params...);
	   };

	   if constexpr( requires{callable(bind_params...); }) {
	   return callable(bind_params...);
	   }
	   else {
	   return fun;
	   }
	   }
	   */

	// improved version
	template<typename Callable, typename ... Params>
		auto curry_fun(Callable callable, Params ... bind_params) {

			if constexpr( requires{callable(bind_params...); }) {
				return callable(bind_params...);
			}
			else {
				return [callable, bind_params...](auto ... passed_params) {
					return curry_fun(callable, bind_params..., passed_params...);
				};
			}
		}
} // namespace

int main() {

	const auto fun0 = myns::curry_fun(myns::add);
	assert(fun0(1,2,3,4) == 10);

	const auto fun1 = myns::curry_fun(myns::add, 1);
	assert(fun1(2,3,4) == 10);

	const auto fun2 = myns::curry_fun(myns::add, 1,2);
	assert(fun2(3,4) == 10);

	const auto fun3 = myns::curry_fun(myns::add, 1,2,3);
	assert(fun3(4) == 10);

	const auto fun4 = myns::curry_fun(myns::add, 1,2,3,4);
	assert(fun4 == 10);     // fun4 in this case is a value and not a function

	// alternate way                                        // similar to above
	assert(10 == myns::curry_fun(myns::add)(1,2,3,4));          // 0
	assert(10 == myns::curry_fun(myns::add, 1)(2,3,4));         // 1
	assert(10 == myns::curry_fun(myns::add, 1, 2)(3,4));        // 2
	assert(10 == myns::curry_fun(myns::add, 1, 2, 3)(4));       // 3
	assert(10 == myns::curry_fun(myns::add, 1, 2, 3, 4));       // 4

	// following assertions are for imoroved version
	assert(10 == myns::curry_fun(myns::add)(1)(2)(3)(4)); 
	assert(10 == myns::curry_fun(myns::add, 1)(2)(3)(4)); 
	assert(10 == myns::curry_fun(myns::add, 1, 2)(3)(4)); 
	assert(10 == myns::curry_fun(myns::add, 1, 2, 3)(4));
	assert(10 == myns::curry_fun(myns::add, 1, 2, 3, 4)); 

	assert(10 == myns::curry_fun(myns::add)(1)()()()()(2)()()()(3)()()(4)); // () retunns functon itself 

	return 0;
}


/**********
  END OF FILE
 ********/

