/****************
 *	This example demonstrates how to write our own bind_front version which behaves like std::bind_front.
 *	This ia an improvement to implementation in ep177 by using std::invoke.
 *
 *	This example also demonstartes to write our own invoke funciton and its various overloads (a few of them are written in this exmaple.).
 *
 *	Also check ep177.
 *
 * ***********/


#include <iostream>
#include <utility>
#include <functional>
#include <string>

struct St {
	static int fun(int a, int b) {
		std::cout << "St::fun " << a << ' ' << b << '\n';
		return a+b;
	}
};

namespace my_exp {

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const noexcept, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) noexcept, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...), Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	// refernce qualified version 
	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const & noexcept , Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const &, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) & noexcept , Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) &, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}


	// rvalue refernce qualified version 
	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const && noexcept , Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) const &&, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) && noexcept , Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	template<typename Class, typename Ret, typename ... Params_t, 
		typename Obj_t, typename ... Args_t>
			auto invoke(Ret (Class::*func)(Params_t ...) &&, Obj_t && obj, Args_t && ... args) {
				return (std::forward<Obj_t>(obj).*func)(std::forward<Args_t>(args) ...);
			}

	// free function overload
	template<typename Ret, typename ... Params_t, typename ... Args_t>
		auto invoke(Ret (*func)(Params_t ...), Args_t && ... args) {
			return (func)(std::forward<Args_t>(args) ...);
		}

	// free function overload
	template<typename Callable, typename ... Params_t>
		auto invoke(Callable && callable, Params_t && ... params) {
			return callable(params ...);
		}

	template<typename F, typename ... Param_t>
		auto bind_front(F && f, Param_t && ... params) {

			return [f = std::forward<F>(f), ...bind_params = std::forward<Param_t>(params)]
				(auto && ... call_params) -> decltype(auto)
				{
					//return std::invoke(f, bind_params ..., std::forward<decltype(call_params)>(call_params) ...);
					return my_exp::invoke(f, bind_params ..., std::forward<decltype(call_params)>(call_params) ...);
					//return f(bind_params ..., std::forward<decltype(call_params)>(call_params) ...);
				};
		}
}

int my_sum(int a, int b) {
	return a+b;
}

int main() {
	std::string lstr = R"(sample string)";

	auto l_f1 = std::bind_front(my_sum, 3);
	std::cout << l_f1(6) << '\n';
	auto l_f2 = std::bind_front(&St::fun, 5);
	std::cout << l_f2(7) << '\n';
	auto l_f3 = std::bind_front(&std::string::size, lstr);
	std::cout << l_f3() << '\n';


	std::cout << '\n';

	auto l_f11 = my_exp::bind_front(my_sum, 3);
	std::cout << l_f11(6) << '\n';
	auto l_f12 = my_exp::bind_front(&St::fun, 5);
	std::cout << l_f12(7) << '\n';
	auto l_f13 = my_exp::bind_front(&std::string::size, lstr);
	std::cout << l_f13() << '\n';

	return 0;
}



/*****
 *	END OF FILE
 * *********/
