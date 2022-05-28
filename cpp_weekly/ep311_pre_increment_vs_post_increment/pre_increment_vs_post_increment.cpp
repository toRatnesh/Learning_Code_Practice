/**************
  This example demonstrates about pre and post increment operators

  For more info visit:
https://www.youtube.com/watch?v=ObVRSNvGitE&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=312

 ***************/

/****
  ++i (pre-increment)
  increment and return new value 

  i++ (post-increment)
  increment and return previous value
  Before usign this, consider why do you need previous value?
  Wihtout optimization this may generate more overhead
 ****/
#include <iostream>
#include <vector> 

void display(const std::vector<int> & coll) {

	auto it = coll.cbegin() + 5;
	while(coll.cend() != it) {
		std::clog << *(it++) << ' ';
		//++it;
	}
	std::clog << '\n';
}

struct myInt {
	int data;

	// pre-increment
	constexpr myInt & operator++() {
		data = data + 1;
		return *this;
	}

	// post-incerement
	// int parameter is a placeholder to distinguish it from pre-increment operator and has to real meaning
	constexpr myInt operator++(int) {
		auto prev_val = *this;
		data = data + 1;
		return prev_val;
	}
};

int main() {
	std::vector lv{1,2,3,4,5,6,7,8,9,10};
	for(auto it = lv.begin()+2; it!= lv.end(); ++it) {
		std::clog << *it << ' ';
	}
	std::clog << '\n';
	display(lv);

	myInt val{10};
	std::clog << (++val).data << '\n'; // new value
	std::clog << (val++).data << '\n'; // previous value
	std::clog << val.data << '\n'; // current value value (which is incremented in previous step)

	return 0;
}

/*****
  END OF FILE
 ******/
