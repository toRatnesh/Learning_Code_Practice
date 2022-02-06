/***************
 *	This example demonstrates how c++20 has made almost all c++ algorithms constexpr.
 *	This results in improved run time performance because result are available at compile time.
 *
 * **************/

#include <iostream>
#include <numeric>
#include <array>

int main() {

	constexpr std::array larr{1,2,3,4,5,6,7,8,9,10};
	constexpr auto res = std::accumulate(larr.begin(), larr.end(), 0);
	static_assert(55 == res);   // static_assert to check result is available at compile time

	return 0;
}



/*****************
 *	END OF FILE
 * **************/
