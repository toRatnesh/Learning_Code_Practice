/**************
 *	This example demonstrates the code bloat when user defines only a destructor in a class. 
 *
 *	To understand this first read following paragraph from Scott Meyers Effective Modern CPP
 *	Item 17: Understand special member function generation.
 *
 *	Declaring a destructor has a potentially significant side effect: it prevents the move operations from being generated. However, creation of the class.s copy operations is unaffected. 
 *	The code is therefore likely to compile, run, and pass its functional testing. That includes testing its move functionality, because even though this class is no longer move-enabled, requests to move it will compile and run. Such requests will, as noted earlier in this Item, cause copies to be made. Which means that code .moving. StringTable objects actually copies them, i.e., copies the underlying std::map<int, std::string> objects. And copying a std::map<int, std::string> is likely to be orders of magnitude slower than moving it. The simple act of adding a destructor to the class could thereby have introduced a significant performance problem! Had the copy and move operations been explicitly defined using .= default., the problem would not have arisen.
 *
 *
 *	NOTE:	To understand the difference compare the assembly generated in presence and absence of user defined destructor.
 *	
 * **************/

#include <iostream>
#include <vector>

struct St{ 
	int data;
	~St();
};

St::~St(){ data = 0; } 

int main() {

	std::vector<St> lvecst;
	lvecst.emplace_back(St{1});
	lvecst.emplace_back(St{2});
	lvecst.emplace_back(St{3});

	return 0;
}

/********
 *	END OF FILE
 * ******/
