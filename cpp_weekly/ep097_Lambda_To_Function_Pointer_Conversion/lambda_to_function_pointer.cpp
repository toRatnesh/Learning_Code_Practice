/**************
 *	This example demonstrates the use of lambda as function pointer and their use as comparator.
 *
 * ****************/

#include <set>

struct myData {
	int data;
};

int main() {

	/* LAMBDA VERSION
	   const auto myDataComparator = [](const myData & lhs, const myData & rhs) {
	   return lhs.data < rhs.data;
	   };
	   std::set<myData, decltype(myDataComparator)> lset{std::move(myDataComparator)};
	   */

	// /* FUNCTION POINTER VERSION
	using comparator_fp_t = bool (*)(const myData & lhs, const myData & rhs);
	std::set<myData, comparator_fp_t> lset{[](const myData & lhs, const myData & rhs) { return lhs.data < rhs.data;} };

	lset.insert(myData{5});

	return 0;
}


/************
 *	END OF FILE
 * ***********/
