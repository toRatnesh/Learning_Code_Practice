/*****************
 *
 * Transparent Lambda Comparators:
 *
 * ********************/

#include <set>

struct myData {
	int data;
};

template<typename T, typename ... Comparator_t>
auto make_set(Comparator_t && ... comparator) {

	struct Compare : std::decay_t<Comparator_t>... {
		using std::decay_t<Comparator_t>::operator()...;
		using is_transparent = int;
	};

	// contructiong Compare object using cpp17 feature
	return std::set<T, std::decay_t<Compare>>{Compare{std::forward<Comparator_t>(comparator)...}}; 
}

int main() {

	auto lset = make_set<myData>(
			[](const myData & lhs, const myData & rhs) { return lhs.data < rhs.data; },
			[](const auto & lhs, const myData & rhs) { return lhs < rhs.data; },
			[](const myData & lhs, const auto & rhs) { return lhs.data < rhs; }
			);

	lset.insert(myData{5});
	lset.count(5);

	return 0;
}

/***************
 *	END OF FILE
 * ****************/
