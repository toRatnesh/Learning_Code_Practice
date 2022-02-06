/*************
 *	This example demonstrates various ways to implement lambda in CPP.
 *
 *	For more info visit tutorial video:
 *	https://www.youtube.com/watch?v=M_Mrk1xHMoo&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=163 
 *
 * ******************/

#include <iostream>

// M-1 lambda using call to itself
constexpr auto recur_lambda_factorial = [] (const auto recur_lambda_factorial, const int num)  { 
	if(num < 0) { return -1; }
	if((1== num) || (0 == num)) { return 1; }
	return (num * recur_lambda_factorial(recur_lambda_factorial, num-1));
};

// M-2  Lambda using another lambda as helper defined outside this lambda
constexpr auto fact_ver2 = [](const int num){
	return  recur_lambda_factorial(recur_lambda_factorial, num);
};

// M-3 Lambda using another lambda as helper defined inside this lambda
constexpr auto fact_ver3 = [](const int num) {

	auto fact_ver3_helper = [](const auto fact_helper, const int num){
		if(num < 0) { return -1; }
		if((1== num) || (0 == num)) { return 1; }
		return num * fact_helper(fact_helper, num-1);
	};

	return fact_ver3_helper(fact_ver3_helper, num);

};

int main() {
	constexpr auto val1 = recur_lambda_factorial(recur_lambda_factorial, 4);
	static_assert(24 == val1);
	std::cout << val1 << '\n';

	constexpr auto val2 = fact_ver2(4);
	static_assert(24 == val2);
	std::cout << val2 << '\n';

	constexpr auto val3 = fact_ver3(4);
	static_assert(24 == val3);
	std::cout << val3 << '\n';

	return 0;
}

/***********
 *	END OF FILE
 * **********/
