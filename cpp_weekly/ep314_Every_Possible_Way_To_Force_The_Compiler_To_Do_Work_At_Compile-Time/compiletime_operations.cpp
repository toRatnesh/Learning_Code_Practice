/***********
  This example demonstrate about various way to do operations at compile time

  For more info visit:
https://www.youtube.com/watch?v=UdwdJWQ5o78&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=315

https://en.cppreference.com/w/cpp/language/constexpr
https://en.cppreference.com/w/cpp/language/consteval
https://en.cppreference.com/w/cpp/language/constinit

 **********/

#include <functional>

constexpr int get_value_constexpr(int val) {
	return (val * 2);
}

consteval int get_value_consteval(int val) {
	return (val * 5);
}

template<auto Value>
consteval const auto make_compile_time() {
	return Value;
}

consteval auto as_constant(auto val) {
	return val;
}

template<typename ... Params>
consteval decltype(auto) consteval_invoke(Params && ... params) {
	return std::invoke(std::forward<Params>(params)...);
}

int main(const int argc, const char * argv[]) {

	// not guaranteed, need to be const
	[[maybe_unused]] constexpr auto val1 = get_value_constexpr(13);  

	// has to be const, static
	[[maybe_unused]] constexpr static auto val2 = get_value_constexpr(15);

	// has to be static (not const)
	[[maybe_unused]] constinit static auto val3 = get_value_constexpr(15);

	[[maybe_unused]] auto val4 = get_value_constexpr(argc);


	// must be a compile time constant 
	// but function must be consteval
	[[maybe_unused]] constexpr auto val21 = get_value_consteval(13);
	[[maybe_unused]] constexpr static auto val22 = get_value_consteval(15);
	[[maybe_unused]] constinit static auto val23 = get_value_consteval(15);
	//[[maybe_unused]] auto val24 = get_value_consteval(argc);    // CE error: 'argc' is not a constant expression

	// downside - werired sysntax
	[[maybe_unused]] auto val31 = make_compile_time<get_value_constexpr(15)>();

	// downside - another functuion call
	[[maybe_unused]] auto val41 = as_constant(get_value_constexpr(15));

	[[maybe_unused]] auto val51 = consteval_invoke(get_value_constexpr, 15);

	return val1+val2+val3+val4+val21+val22+val23+val31+val41;
}

/*****
  END OF FILE
 ****/
