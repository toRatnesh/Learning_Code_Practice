/**************
 *	This example demonstrates the use of cpp20 for init statement.
 * **************/

#include <iostream>
#include <array>

struct St{
	std::array<int , 5> data{11, 12, 13, 14, 15};
	const auto & getStData() {
		return data;
	}
};

St getSt() {
	return St{};
}

auto getArray() {
	std::array data{11, 22, 33, 44, 55};
	return data;
}

int main() {
	std::array lar{1, 2, 3, 4, 5};

	auto total = 0;
	for(int weight_val = 0;     // for init statement
			const auto val : lar) {
		total += (val * (++weight_val));
	}
	std::cout << total << '\n';
	total = 0;



	for(const auto val : getArray()) {
		total += val;
	}
	std::cout << total << '\n';
	total = 0;


	// real use
	//  the temporary St object is destroyed before the for loop's body begins executing, causing undefined values for val
	//  For more detail check TheParkourPenguin's comment on tutorial video
	//for(const auto val : getSt().getStData()) 
	for(auto sto = getSt();     // for init statement
			const auto val : sto.getStData())   
	{
		total += val;
	}
	std::cout << total << '\n';

	return 0;
}

/**********
 *	END OF FILE
 * ***********/
