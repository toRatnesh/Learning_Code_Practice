/****************
 *	In this tutorial Jason talks about how CPP algorithms can be used to replace loops in our code.
 *	Using algorithms to replace our loop leads to better readability and syntax.
 * ******************/

#include <iostream>
#include <vector>
#include <numeric>

float getVectorSum(const std::vector<float> & flt_vec) {

	/*
	   float res = 0.0f;
	   for(auto val : flt_vec) {
	   res += val;
	   }
	   return res;
	   */

	// std::accumulate algorithm could be used to replace above loop 
	return std::accumulate(flt_vec.begin(), flt_vec.end(), 0.0f);
}

int main() {

	std::vector<float> lfv{1.2f, 3.4f, 5.6f, 8.7f};
	auto res = getVectorSum(lfv);
	std::cout << res << '\n';

	return 0;
}


/********
 *	END OF FILE
 * ********/
