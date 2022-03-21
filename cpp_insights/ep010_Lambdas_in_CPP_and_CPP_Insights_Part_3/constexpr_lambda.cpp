/*************
  This example demonstrates about implicitly constexpr behavior of lambdas in C++ since C++17

  For more info visit:
https://www.youtube.com/watch?v=VwJjySHan6g
cpp weekly episodes about lambda
 ***************/

int main() {
	auto max = [](auto x, auto y){ return (x>y)?x:y; };
	// calling max in constant context which shows its constexpr behavior (since C++17)
	static_assert(max(2,3) == 3);
	static_assert(max(5,3) == 5);
	static_assert(max(3,3) == 3);
	return 0;
}

/*******
  END OF FILE
 *******/
