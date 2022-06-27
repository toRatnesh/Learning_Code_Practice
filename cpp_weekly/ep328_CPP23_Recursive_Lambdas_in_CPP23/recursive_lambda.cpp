/****************
  This example demonstrates about how easily recursive lambda can be implemented
  using C++23 deducing this feature

  Other episodes on recursive lambda are:
  ep162

  For more info visit:
https://www.youtube.com/watch?v=hwD06FNXndI&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=329
 **************/

int main() {
	//constexpr auto factorial = []<typename Self>(this const Self & self, int val) 
	constexpr auto factorial = [](this const auto & self, int val) 
	{
		if(1 == val) {
			return val;
		}
		else {
			return val * self(val - 1);
		}
	};

	return factorial(4);
}

/*******
  END OF FILE
 *********/
