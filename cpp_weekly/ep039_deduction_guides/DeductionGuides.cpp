/*******
 *	Deduction Guides:
 *	Reference:	https://en.cppreference.com/w/cpp/language/class_template_argument_deduction
 *
 *	User-defined deduction guides
 *	The syntax of a user-defined deduction guide is the syntax of a function declaration with a trailing return type, 
 *	except that it uses the name of a class template as the function name:
 *
 *	explicit-specifier(optional) template-name ( parameter-declaration-clause ) -> simple-template-id ;		
 *	User-defined deduction guides must name a class template and must be introduced within the same semantic scope of the 
 *	class template (which could be namespace or enclosing class) and, for a member class template, must have the same access,
 *	but deduction guides do not become members of that scope.
 *
 * *******/

#include <iostream>
#include <functional>


// NOTE:	I have created this deduction guide only for learning purpose.
// 		At the time of compilation of this code it was working even without user defined deduciton guide.

namespace std {

	template<typename Ret, typename ... Arg>
		function(Ret (*)(Arg...)) -> function<Ret (Arg...)>;

	// for class non-const member function
	template<typename Ret, typename Class, typename ... Arg> 
		function(Ret (Class::*)(Arg...)) -> function<Ret (Class &, Arg...)>;

	// for class const member function
	template<typename Ret, typename Class, typename ... Arg> 
		function(Ret (Class::*)(Arg...) const) -> function<Ret (const Class &, Arg...)>;

}
void test_deduction() {
	std::cout << "test deduction" << '\n';
}

void test_deduction2(int m , const std::string & arg_msg) {
	std::cout << "test deduction " << m << ' ' << arg_msg << '\n';
}

struct MyClass {
	void member_fun1() { std::cout << "testing deduction for member function" << '\n'; }
	void member_fun2() const { std::cout << "testing deduction for const member function" << '\n'; }
};

int main() {

	std::function fb(&test_deduction);
	fb();

	std::function fb2(&test_deduction2);
	fb2(1, R"(Learning deduction guide)");

	MyClass mc;
	std::function mf1(&MyClass::member_fun1);
	mf1(mc);

	const MyClass mc2;
	std::function mf2(&MyClass::member_fun2);
	mf2(mc2);

	return 0;
}


/*****
 *	END OF FILE
 * *****/
