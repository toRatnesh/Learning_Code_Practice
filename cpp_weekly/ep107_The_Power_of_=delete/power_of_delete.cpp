/*******************************
 * 	This example demonstrates the use of =delete to delete a function.
 * 	If we are calling a function which is deleted then we will get compilation error.
 *
 * 	In case when both template and non-template version is present:
 * 	Name lookup finds both declarations,
 * 	overload resolution picks the non-template function as a better match
 * 	and if that function is deleted then compiler generates an error because it's been deleted.
 *
 * 	You can still instantiate the template function with T=double by explicitly specifying the template argument 
 * 	(e.g. some_fun<double>(1.5);).
 *
 *****************/
#include <iostream>

struct St {
	constexpr int fun(int arg) const noexcept { return arg+1; }
	int fun(double arg) const noexcept = delete;
	int fun(float arg) const noexcept = delete;
	int fun(bool arg) const noexcept = delete;

	// C++14

	template <typename T, 
		 std::enable_if_t<((std::is_integral<T>::value || std::is_floating_point<T>::value) && !std::is_same<T, bool>::value), bool> = true 
			 >

			 /* // C++17
			    template <typename T,
			    std::enable_if_t<((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>), bool> = true 
			    >
			    */

			 /* // C++20  
			    template <typename T>
			    requires((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
			    */
			 constexpr auto fun(T  targ) const noexcept {
				 return targ+2;
			 }

};

int main() {

	St s;
	// using function 
	std::cout << s.fun(5) << '\n';
	// all following versions uses implicit conversion to int
	// also since this is not a constructor or conversion function we can not declare it as explicit
	// so wee need to delete the verions which we do not want to be called
	//s.fun(5.7);	// CE: error: use of deleted function 'int St::fun(double) const'
	//s.fun(4.6f);
	//s.fun(true);

	// using template function
	std::cout << s.fun<int>(5) << '\n';
	std::cout << s.fun<double>(5.7) << '\n';
	//std::cout << s.fun<bool>(true) << '\n'; // error: no matching function for call to 'St::fun<bool>(bool)'
							// ... template argument deduction/substitution failed ...
	//std::cout << s.fun<std::string>("sample string") << '\n';

	return 0;
}



/**************
 *	END OF FILE
 * *********/
