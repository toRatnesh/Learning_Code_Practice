/********
  This example demonstrates about STL vector of bool

// member types of vector<bool> are diffrent than vector<T>
// expecially notice the differnce of reference
reference       proxy class representing a reference to a single bool (class)
const_reference bool

For more info visit:
https://en.cppreference.com/w/cpp/container/vector_bool

 *******/

#include <iostream>
#include <vector>

int main() {

	std::clog << "=== vector<int> ===\n";
	std::vector<int > vi;
	vi.push_back(1);
	std::clog << "size: " << vi.size() << ' ' << " capacity: " << vi.capacity() << '\n';
	vi.push_back(2);
	std::clog << "size: " << vi.size() << ' ' << " capacity: " << vi.capacity() << '\n';
	vi.push_back(3);
	std::clog << "size: " << vi.size() << ' ' << " capacity: " << vi.capacity() << '\n';
	for(auto val : vi) {
		std::clog << val << ' ';
	}
	std::clog << '\n';

	for(auto & valref : vi) {
		std::clog << valref << ' ';
	}
	std::clog << '\n';

	{
		std::clog << "=== vector<bool> ===\n";
		std::vector<bool> vb;
		vb.push_back(1);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';
		vb.push_back(0);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';
		vb.push_back(1);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';

		for(auto val : vb) {
			std::clog << val << ' ';
		}
		std::clog << '\n';

	}

	{
		std::clog << "=== vector<bool> ===\n";
		std::vector<bool> vb;
		vb.push_back(true);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';
		vb.push_back(false);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';
		vb.push_back(true);
		std::clog << "size: " << vb.size() << ' ' << " capacity: " << vb.capacity() << '\n';

		for(auto val : vb) {
			std::clog << val << ' ';
		}
		std::clog << '\n';

		// proxy object demonstrations
		//for(auto & valref : vb) // error: cannot bind non-const lvalue reference of type 'std::_Bit_reference&' to an rvalue of type 'std::_Bit_iterator::reference'
		//for(const auto & valref : vb) // this will move via copy
		for(auto && valref : vb) {
			std::clog << valref << ' ';
		}
		std::clog << '\n';

		auto val = vb.front();
		val = false; 
		for(auto val : vb) {
			std::clog << val << ' ';
		}
		std::clog << '\n';    

		// vector<bool> specific member functions
		vb.flip();
		for(auto val : vb) {
			std::clog << val << ' ';
		}
		std::clog << '\n';

		std::vector<bool> vb2{true, false, true, false};
		vb2.swap(vb);
		for(auto val : vb) {
			std::clog << val << ' ';
		}
		std::clog << '\n';
	}

	return 0;
}

/****
  END OF FILE
 ****/


