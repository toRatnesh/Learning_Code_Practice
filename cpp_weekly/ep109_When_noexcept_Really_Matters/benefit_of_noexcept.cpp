/**********
 *	This example demonstrates benefit of noexcept function using vector.
 *
 *	When vector is resized vector elements are copied from old vector to new one using copy constructor,
 *	 in case move constructor is not defined as noexcept. 
 *	 When move constructor is defined as noexcept elements are copied using move constructor.
 *
 *	 Since move constructor has better performance than copy constructor it improves the performance. 
 *
 * ********/


#include <iostream>
#include <vector>

struct St {
	int data;

	St(int arg) : data(arg) { std::puts("Parameterized constructor"); };
	St(const St & other) : data(other.data) { std::puts("copy constructor"); }
	St& operator=(const St & other)  { 
		std::puts("copy assignment"); 
		if(this != &other) {
			data = other.data;
		}
		return *this;
	}

	St(St && other) noexcept : data(other.data) {
		other.data = 0;
		std::puts("move constructor");       
	}

	St& operator=(St && other)   { 
		std::puts("move assignment"); 
		if(this != &other) {
			data = other.data;
			other.data = 0;
		}
		return *this;
	}

	~St() { std::puts("destructor");  }

};

int main() {

	std::vector<St> vst;
	std::cout << vst.capacity() << '\n';
	vst.emplace_back(3);
	std::cout << vst.capacity() << '\n';
	vst.emplace_back(5);
	std::cout << vst.capacity() << '\n';
	vst.emplace_back(8);
	vst.emplace_back(11);

	return 0;
}

/**********
 *	END OF FILE
 * **********/
