/*********
 *	This example demonstrates about use of explicit specifier.
 *
 *	Implicit cost to an user defined type is costly and may introduce bug, explicit specifier stops implicit conversion.
 *
 *	For more info visit:
 *	Tutorial:	https://www.youtube.com/watch?v=CMmkoy24XhU&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=277
 *	https://en.cppreference.com/w/cpp/language/explicit
 *	https://en.cppreference.com/w/cpp/types/is_trivial
 *
 * ********/

#include <iostream>
#include <type_traits>
template <typename T>
struct St {
	St() = default;
	St(const T & other) : m_tval(other) { std::puts("St's copy constructor"); }
	St(T&& other) : m_tval(std::move(other)) { std::puts("St's move constructor"); }
	operator T () const { return m_tval; } 

	private:
	T m_tval;
};
void st_fun1(const St<int> & parm) { std::puts("St's fun1"); }
void st_fun2(int) { std::puts("St's fun2"); }

template <typename T>
struct Ste {
	Ste() = default;
	/* SCENARIO -1 | Only explicit cast
	   explicit Ste(const T & other) : m_tval(other) { std::puts("Ste's copy constructor"); }
	   explicit Ste(T&& other) : m_tval(std::move(other)) { std::puts("Ste's move constructor"); }
	   explicit operator T () const { return m_tval; } 
	   */
	/* SCENARIO -2 | Implicit cast for trivially copyable types */
	explicit(!std::is_trivial_v<T>) Ste(const T & other) : m_tval(other) { std::puts("Ste's copy constructor"); }
	explicit(!std::is_trivial_v<T>) Ste(T&& other) : m_tval(std::move(other)) { std::puts("Ste's move constructor"); }
	explicit(!std::is_trivial_v<T>) operator T () const { return m_tval; } 
	private:
	T m_tval;
};
void ste_fun1(const Ste<int> & parm) { std::puts("Ste's fun1"); }
void ste_fun2(int) { std::puts("Ste's fun2"); }

int main() {
	st_fun1(1);             // implicit conversion to St<int>
	st_fun2(St<int>(5));    // implicit conversion to int usning conversion function
	st_fun1((St<int>)2);    // explicit cast
	/* SCENARIO -1 | Only explicit cast */
	//ste_fun1(1);                // implicit conversion fails
	//ste_fun2(Ste<int>(5));      // implicit conversion fails
	ste_fun1((Ste<int>)2);        // explicit cast

	/* SCENARIO -2 | Implicit cast for trivially copyable types */
	ste_fun1(1);                // implicit conversion fails
	ste_fun2(Ste<int>(5));      // implicit conversion fails
	ste_fun1((Ste<int>)2);        // explicit cast
	return 0;
}

/******
 *	END OF FILE
 * ******/
