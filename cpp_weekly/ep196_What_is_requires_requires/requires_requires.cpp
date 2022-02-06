/*********
 *	This example demonstrates what is requires requires and how to write improved constraints using concept to eliminate it.
 *
 *	For more info visit:
 *	https://en.cppreference.com/w/cpp/language/constraints
 *
 * **********/

#include <iostream>

template<typename T>
concept has_call_operator = requires { &T::operator(); };

template<typename FuncObj>
//requires requires { &FuncObj::operator(); } // this is ad hoc constraint
// requires requires is used when missing concept or type_traits or something that may be well defined

// improvement 
requires has_call_operator<FuncObj>                                           
auto call_func_obj(FuncObj fnobj_param) {
	return fnobj_param();
}

int global_fun() {
	std::puts("global func");
	return 0;
}

int main() {
	call_func_obj( []{ std::puts("lambda"); } );

	// due to constraint this fails to compile
	// error: use of function 'auto call_func_obj(FuncObj) [with FuncObj = int (*)()]' with unsatisfied constraints
	call_func_obj(global_fun);

	return 0;
}

/*********
 *	END OF FILE
 * **********/
