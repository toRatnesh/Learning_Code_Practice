/***************
  This example demonstrates about how to
  store lambda in a container

 ****************/

#include <iostream>
#include <vector>

auto make_lambda_multiply_by( int val) {
	return [val](const int param){ return val * param; };
}

int main() {
	auto get10 = [](){return 10;};
	auto getDouble = [](const int val){return val * 2;};
	auto getSquare = [](const int val){return val * val;};

	std::vector<decltype(get10)> lvec1;
	lvec1.push_back(get10);
	lvec1.push_back(get10);
	//lvec1.push_back(getDouble); // Compilation error

	std::vector<decltype(getDouble)> lvec2;
	lvec2.push_back(getDouble);
	//lvec2.push_back(getSquare); // Compilation error

	std::vector<decltype(make_lambda_multiply_by(2))> lvec3;
	lvec3.push_back(make_lambda_multiply_by(3));
	lvec3.push_back(make_lambda_multiply_by(7));
	lvec3.push_back(make_lambda_multiply_by(11));

	return 0;
}

/*******
  END OF FILE
 *****/

