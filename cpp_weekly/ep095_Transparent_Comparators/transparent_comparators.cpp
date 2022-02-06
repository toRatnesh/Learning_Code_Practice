/*****************
 *	Transparent Comparators:
 *
 *
 *
 * ********************/

#include <set>

struct myData {
	int data;
};

struct myDataComparator {
	bool operator()(const myData & lhs, const myData & rhs) const {
		return lhs.data < rhs.data;
	}
	template<typename T>
	bool operator()(const myData & lhs, const T & rhs) const {
		return lhs.data < rhs;
	}
	template<typename T>
	bool operator()(const T & lhs, const myData & rhs) const {
		return lhs < rhs.data;
	}

	using is_transparent = int;
};

int main() {
	std::set<myData, myDataComparator> lset;
	lset.insert(myData{3});
	lset.insert(myData{4});
	lset.insert(myData{5});

	lset.count(3);

	return 0;
}

/***************
 *	END OF FILE
 * ****************/
