/**********
  This example demonstrates about const member function
  For more info visit:
https://www.youtube.com/watch?v=bqd9ILyQRxQ&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=317
https://en.cppreference.com/w/cpp/language/member_functions#const-_and_volatile-qualified_member_functions
 **********/

#include <string>
#include <iostream>

class Student {
	private:
		std::string name;
		int standard;

	public:

        Student(const std::string name, const int standard) : name(name), standard(standard) { }

		void constMemFun() const {
			std::clog << "name: " << name << ", ";
			std::clog << "standard: " << standard << '\n';

			//++standard; // CE: error: increment of member 'Student::standard' in read-only object
		}

		int nonConstMemFun() {
			++standard;
			return standard;
		}

};

int main() {
	std::clog << "--- Const and non-const objects ---\n";
	const Student cst{"Student_1", 1};
	Student st{"Student_3", 3};

	cst.constMemFun();
	st.constMemFun();

	//cst.nonConstMemFun(); // CE: error: passing 'const Student' as 'this' argument discards qualifiers [-fpermissive]
	st.nonConstMemFun();

	cst.constMemFun();
	st.constMemFun();

	std::clog << "--- Const reference to const and non-const object ---\n";

	const Student & cstref1 = cst;
	const Student & cstref2 = st;

	cstref1.constMemFun();
	cstref2.constMemFun();

	//cstref1.nonConstMemFun(); // CE: error: passing 'const Student' as 'this' argument discards qualifiers [-fpermissive]
	//cstref2.nonConstMemFun(); // CE: error: passing 'const Student' as 'this' argument discards qualifiers [-fpermissive]

	cstref1.constMemFun();
	cstref2.constMemFun();

	std::clog << "--- Non-const Reference to non-const object (to const object is an error) ---\n";

	//Student & stref1 = cst; // CE: error: binding reference of type 'Student&' to 'const Student' discards qualifiers
	Student & stref2 = st;

	//stref1.constMemFun();
	stref2.constMemFun();

	//stref1.nonConstMemFun();
	stref2.nonConstMemFun();

	//stref1.constMemFun();
	stref2.constMemFun();

	return 0;
}

/*******
  END OF FILE
 *****/
