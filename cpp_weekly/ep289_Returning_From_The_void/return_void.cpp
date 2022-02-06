/***********
 *	This example deonstrates about void return type from a function.
 *
 *
 *	This ability to return 'void' from a function that returns 'void' is actually potentially very helpful and 
 *	when combined with 'auto' or in the case of 'perfect returning' then we can get the exact type back and 
 *	actually potentially simplify a lot of code. 
 *	We don.t have to worry about whether or not a function returns 'void' or a value even though 'void' is not a regular type.
 *
 * *************/


void do_something() { }
void do_something_else() { }

int val = 5;
int return_int() { return 5; }
int & return_int_ref() { return val; }

enum VAL {
		V1,
		V2
};

void call_a_fun(VAL v) {
		switch(v) {
				case V1: return do_something();
				case V2: return do_something_else();
		}
}

auto call(auto func) {
		return func();
}

decltype(auto) call2(auto func) {
		return func();
}

int main() {
		call(do_something);
		call(do_something_else);

		[[maybe_unused]] int ival = call(return_int);
		// CE error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
		//int & irval = call(return_int_ref); 
		ival = call(return_int_ref); 

		ival = call2(return_int);
		[[maybe_unused]] int & irval = call2(return_int_ref);

		return 0;
}

/********
 *	ENF OF FILE
 * ********/
