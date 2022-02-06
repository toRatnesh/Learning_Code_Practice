/*****************
 *	This example demonstrates the use of custom comparators for containers.
 *
 * *************/

#include <set>

struct myData {
	int data;
};

struct myDataComparator {
	bool operator()(const myData & lhs, const myData & rhs) const {
		return lhs.data < rhs.data;
	}
};

int main() {

	std::set<myData, myDataComparator> lset;
	lset.insert(myData{5});

	return 0;
}

/*********
 *	END OF FILE
 * ********/
