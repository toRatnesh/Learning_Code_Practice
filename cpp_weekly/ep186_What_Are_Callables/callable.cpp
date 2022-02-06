/************
 *	This example demonstrates about callable.
 *
 *	Callable:
 *	A Callable type is a type for which the INVOKE operation (used by, e.g., std::function, std::bind, and std::thread::thread) is applicable. This operation may be performed explicitly using the library function std::invoke. (since C++17)
 *
 *	Fore more info visit:
 *	https://en.cppreference.com/w/cpp/named_req/Callable
 *
 * **************/

#include <iostream>
#include <functional>

struct St {
	int i;
	int j;

	int get_i() const noexcept { return i; }
	int get_j() const { return j; }

	int set_i(const int val)  { i = val; return i; }
	int set_j(const int val) { j = val; return j; }
	bool set_i_j(const int a, const int b) { i = a; j = b; return true; } 

	int operator()() {
		std::puts("operator()");
		return 0;
	}
};

int main() {
	St st{13, 23};
	St *st_ptr = &st;

	// function pointer
	int (St::*mem_fn_ptr)() const = &St::get_j;
	std::cout << (st.*mem_fn_ptr)() << '\n';
	mem_fn_ptr = &St::get_i;
	std::cout << (st_ptr->*mem_fn_ptr)() << '\n';
	std::cout << std::invoke(mem_fn_ptr, st) << '\n';

	// object pointer
	int St::*mem_obj_ptr = &St::i;
	std::cout << st.*mem_obj_ptr << '\n';
	mem_obj_ptr = &St::j;
	std::cout << st_ptr->*mem_obj_ptr << '\n';
	std::cout << std::invoke(mem_obj_ptr, st) << '\n';

	st();
	(*st_ptr)();

	return 0;
}


/*********
 *	END OF FILE
 * *********/
