/**********
 *	This example demonstrates the use and benefits of emplace_back.
 *	This example also demonstrates how emplace is different from insert and push_back while creating an inserting object.
 *
 *	since c++17:
 *	emplace_back returns a reference to the inserted element.
 *	This reference helps to subsquelnty call other methods.
 *
 *
 * **********/

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

	St(St && other) : data(other.data) {
		other.data = 0;
		std::puts("move constructor");       
	}

	St& operator=(St && other)  { 
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
	//vst.insert(vst.begin(), St(100)); // Parameterized constructor, move constructor, destructor, destructor
	//vst.push_back(St(3));         // Parameterized constructor, move constructor, destructor, destructor
	
    // this is wrong way to use emaplce_back
	//vst.emplace_back(St(3));      // Parameterized constructor, move constructor, destructor, destructor

	//vst.emplace_back(3);          // Parameterized constructor, destructor




	// Another use of emplace back since C++17
	std::vector<std::vector<int>> v;
	v.emplace_back(3, 1).push_back(4);
	v.emplace_back(7, 9).pop_back();

	for(const auto & lv : v) {
		for(const auto val : lv) {
			std::cout << val << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}

/*********
 *	END OF FILE
 * *********/
