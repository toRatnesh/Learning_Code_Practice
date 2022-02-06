/*************
 *	This example demonstrates the use of assignment operators in cpp.
 *	This may not contain all possible versions.
 *
 * *************/

#include <utility>

struct S {

	S& operator=(S & s) & = default;
	S& operator=(S && s) & = default;
	S& operator=(const S & s) & = default;

	S& operator=(S & s) && = delete;
	S& operator=(S && s) && = delete;
	S& operator=(const S & s) && = delete;

	S& operator=(const S && s) & = delete;    // moving from a const rvalue has no meaning
	//S& operator=(const S && s) && = delete;    // moving from a const rvalue has no meaning
	S& operator=(const S && s) && { return *this; };

	// assignment to const object is meaning less so these versions cannot be default 
	S& operator=(S & s) const & = delete;
	S& operator=(S && s) const & = delete;
	S& operator=(const S & s) const & = delete;
	S& operator=(const S && s) const & = delete;    // moving from a const rvalue has no meaning

	S& operator=(S & s) const && = delete;
	S& operator=(S && s) const && = delete;
	S& operator=(const S & s) const && = delete;
	S& operator=(const S && s) const && = delete;    // moving from a const rvalue has no meaning

};

int main() {
	/*
	// assignment to temporary object, this is illogical
	// to fix this, delete rvalue reference qualified version
	// S{} = S{};
	*/

	S s{};
	S s2{};
	const S s3{};

	s = std::move(s2);
	//s= std::move(s3);

	// user defined rvalue reference qualified version
	S{} = std::move(s3);    

	return 0;
}

/**********
 *	END OF FILE
 * **********/
