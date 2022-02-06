/*****************
  This exmaple demonstrates the use of local function.
  Although local fun are not allowed in CPP. 
  We can achieve in various way by using local classes and lambda.

  For more info visit:
  Tutorial video: https://www.youtube.com/watch?v=-EDx6fC6mkQ


 ************************/

#include <iostream>
#include <vector>
#include <algorithm>

void display_vec(std::vector<int> & fp_vec) {
	for(const auto elem: fp_vec) {
		std::clog << elem << ' ';
	}
	std::clog << '\n';
}

int main() {

	struct S {
		static int getValue1() {
			return 1;
		}

		int getValue2() {
			return 2;
		}
	};
	std::clog << S::getValue1() << '\n';
	std::clog << S().getValue2() << '\n';

	struct getValue3 {
		int operator()() {
			return 3;
		}
	};
	std::clog << getValue3()() << '\n';

	auto getValue4 = [](){ return 4;};
	std::clog << getValue4() << '\n';

	std::vector<int> lv(10);

	std::fill(lv.begin(), lv.end(), S::getValue1());
	display_vec(lv);

	std::fill(lv.begin(), lv.end(), S().getValue2());
	display_vec(lv);

	std::fill(lv.begin(), lv.end(), getValue3()());
	display_vec(lv);

	std::fill(lv.begin(), lv.end(), getValue4());
	display_vec(lv);

	return 0;
}

/******
  END OF FILE
 ********/
