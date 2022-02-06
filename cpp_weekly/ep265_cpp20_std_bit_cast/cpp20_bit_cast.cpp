/*************
	This example demonstrates about use of CPP-20 std::bit_cast.

****************/


//#include <fmt/format.h>

#include <iostream>
#include <iomanip>
#include <string.h>

void with_c_cast () {
	std::cout << __func__ << '\n';
	// this code is not allowed in constexpr (due to reinterpret cast)
	float f= 0.0032435435f;
	float n = f;
	*((int *)&n) += ((f > 0) ? 1 : -1);     // this has UB

	//fmt::print("{} -> {} \n", f, n);
	std::cout << std::setprecision(8) << f << " -- " << n << '\n';

	return ;
}

void with_memcpy () {
	std::cout << __func__ << '\n';
	// this code is not allowed in constexpr (due to memcpy)
	float f= 0.0032435435f;

	int i;
	std::memcpy(&i, &f, sizeof(f));
	i += ((f > 0) ? 1 : -1);

	float n;
	std::memcpy(&n, &i, sizeof(f));

	//fmt::print("{} -> {} \n", f, n);
	std::cout << std::setprecision(8) << f << " -- " << n << '\n';

	return ;
}

void with_bit_cast () {
	std::cout << __func__ << '\n';
	float f= 0.0032435435f;

	int i = std::bit_cast<int>(f);
	i += ((f > 0) ? 1 : -1);

	float n = std::bit_cast<float>(i);

	//fmt::print("{} -> {} \n", f, n);
	std::cout << std::setprecision(8) << f << " -- " << n << '\n';

	return ;
}

int main() {
	with_c_cast();      std::cout << '\n';
	with_memcpy();      std::cout << '\n';
	with_bit_cast();    std::cout << '\n';

	return 0;
}

/******
    END OF FILE
 *******/
