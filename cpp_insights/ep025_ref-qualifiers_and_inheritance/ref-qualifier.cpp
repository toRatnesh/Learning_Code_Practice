/*********
  This example demonstrates about reference qualifiers

  int fun() const &;
  int fun()		&;
  int fun()		&&;

// ref: https://stackoverflow.com/questions/28066777/const-and-specifiers-for-member-functions-in-c
const& means, that this overload will be used only for const, non-const and lvalue object
& means, that this overload will be used only for non-const object
&& means, that this overload will be used only for rvalue object

For more info check 
https://en.cppreference.com/w/cpp/language/member_functions
https://www.youtube.com/watch?v=Fsi3JpYCsUM

 *********/


struct Base {
	Base & operator=(const Base & ) & = default;	// for non-const object
};


struct Derived : Base {
	Derived & operator=(const Derived & ) & = default;	// for non-const object
};

int main() {  
	//Base b{};
	//Base{} = b;

	Derived d{};
	Derived{} = d;

	return 0;
}

/*********
  END OF FILE
 ********/
