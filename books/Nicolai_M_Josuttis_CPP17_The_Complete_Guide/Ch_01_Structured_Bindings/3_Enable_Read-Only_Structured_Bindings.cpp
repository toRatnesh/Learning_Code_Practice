/********
Reference:  C++17 - The Complete Guide | Nicolai M. Josuttis

Structured Bindings
Structured bindings allow you to initialize multiple entities by the elements or members of an object.

Enable Read-Only Structured Bindings
-> Enable getters for all members
-> Extend tuple_size for count of members
-> Extend tuple_element for type of members

 **********/

#include <iostream>
#include <string>
#include <utility>

namespace nonstd {
	class Student {
		private:
			std::string m_name;
			std::string m_department;
			uint32_t m_rollno;

		public:
			Student(std::string name, std::string department, uint32_t rollno)
				: m_name(name), m_department(department), m_rollno(rollno) {}

			std::string name() const { return m_name; }
			std::string department() const { return m_department; }
			uint32_t rollno() const { return m_rollno; }
	};

	/*
	   template<std::size_t> auto get(const Student &);
	   template<> auto get<0>(const Student & st) { return st.name(); }
	   template<> auto get<1>(const Student & st) { return st.department(); }
	   template<> auto get<2>(const Student & st) { return st.rollno(); }
	   */
	// following get() function can replace above get
	template<std::size_t Idx>
		auto get(const Student & st) {
			static_assert(Idx < 3);
			if constexpr(0 == Idx) { return st.name(); }
			else if constexpr(1 == Idx) { return st.department(); }
			else { return st.rollno(); }
		}
}  // namespace nonstd

// to Enable Read-Only Structured Bindings
template<> struct std::tuple_size<nonstd::Student> { static constexpr int value = 3; };
template<> struct std::tuple_element<2, nonstd::Student> { using type = uint32_t; };
template<std::size_t Idx> struct std::tuple_element<Idx, nonstd::Student> { using type = std::string; };

int main() { 
	nonstd::Student st("student-1", "ece", 123);
	auto [n, d, r] = st;
	std::clog << n << ' ' << d << ' ' << r << '\n';
	std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
	std::string str = std::move(n);
	d = "cse";
	r = 456;
	std::clog << n << ' ' << d << ' ' << r << '\n';
	// changing structure bind values has no effect on original object
	std::clog << st.name() << ' ' << st.department() << ' ' << st.rollno() << '\n';
	std::clog << str << '\n';

	return 0; 
}

/*****
  END OF FILE
 ******/

