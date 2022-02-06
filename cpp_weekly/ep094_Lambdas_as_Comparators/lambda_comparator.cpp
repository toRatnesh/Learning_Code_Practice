/**************
 *
 *	This exmaple demonstrates how to use lambda as comparator.
 *
 * **************/


#include <set>

struct myData {
	int data;
};

int main() {

	const auto myDataComparator = [](const myData & lhs, const myData & rhs) {
		return lhs.data < rhs.data;
	};


	/**********
	 * error: use of deleted function 'main()::<lambda(const myData&, const myData&)>::<lambda>()'
	 * note: a lambda closure type has a deleted default constructor
	 * 
	 * C++20 : in c++20 this code will work fine because 
	 * stateless lambdas will be default constructible and assignable in c++20
	 * *******/
	//      std::set<myData, decltype(myDataComparator)> lset;

	std::set<myData, decltype(myDataComparator)> lset{myDataComparator};
	lset.insert(myData{5});


	//      using cpp17 class template argument type deduction 
	std::set lset2{ {myData{5}}, myDataComparator};

	//	using lambda directly as comparator
	std::set lset3{ {myData{5}}, 
		[](const myData & lhs, const myData & rhs) {
			return lhs.data < rhs.data;
		}
	};

	return 0;
}


/**************
 *	END OF FILE
 * *************/
