/*************
  This example demonstrate about template instantiation and explicit template instantiation.

  For more info visit:
  Back to Basics: Compiling and Linking - Ben Saks - CppCon 2021
https://www.youtube.com/watch?v=cpkDQaYttR4&list=PLHTh1InhhwT4TJaHBVWzvBOYhp27UO7mI&index=7

 **************/


#include <utility>

// hader file
template <typename T>
struct S {
	auto fun(T t) {
		return t;
	}

	auto fun2(T t) {
		return t;
	}
};

// explicit specilization declaration for int type for fun (not fun2)
// this ensures that code for int type is generated always
template <>
struct S<int> {
	int fun(int t);
};


template<typename T>
struct Ct {
	auto fun(T val) {
		return val;
	}

	auto fun2(T t) {
		return t;
	}
};

// explicit class instantiation declaration
extern template
struct Ct<double>;

template<typename T> 
void mySwap(T & left, T & right) {
	T temp(std::move(left));
	left = std::move(right);
	right = std::move(temp);
}

// explicit function instantiation declaration
extern template
void mySwap(int & left, int & right);


/*******
  END OF FILE
 *********/
