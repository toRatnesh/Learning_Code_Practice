/**********
  This example demonstrates about
  compiler implementation difference of const and non-const member function

  To check compiler implementaion difference visit this episode on youtube

  For more info visit:
https://www.youtube.com/watch?v=4etjb2_KAaE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=318
https://en.cppreference.com/w/cpp/language/member_functions#const-_and_volatile-qualified_member_functions
 **********/

#include <iostream>
#include <string>

class Student {
	private:
		std::string name;
		int standard;

	public:
		Student(const std::string name, const int standard)
			: name(name), standard(standard) {}

		/*
		//const and non const member functions participate in compiletime overload
		// if we are not calling one of them then compiler may optimized it out and
		will not generate its definition as its not needed
		*/
		int fun() const {
			std::clog << "name: " << name << ", ";
			std::clog << "standard: " << standard << '\n';

			//++standard; // CE: error: increment of member 'Student::standard' in
			// read-only object
			return 0;
		}

		int fun() {
			++standard;
			return standard;
		}
};

int main() {
	const Student cst{"Student_1", 1};
	cst.fun();

	/*
	//const and non const member functions participate in compiletime overload
	// if we are not calling one of them then compiler may optimized it out and
	will not generate its definition as its not needed 
    
    Student st{"Student_1", 1}; 
    st.fun();
	*/

	return 0;
}

/*****
	END OF FILE
****/
