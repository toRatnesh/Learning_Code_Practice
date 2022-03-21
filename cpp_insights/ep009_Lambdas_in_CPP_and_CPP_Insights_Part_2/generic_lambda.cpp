/*************
  This example demonstrates about generic lambdas in C++

  For more info visit:
https://www.youtube.com/watch?v=EnpiC7e054M
cpp weekly episodes about lambda
 ***************/

int main() {  
	auto l = [](auto m, auto n) { return m*n; };
	auto retd = l(2.5,3.3);
	auto reti = l(3,4);
	auto retid = l(3,5.5);
	auto retdi = l(5.5,3);
	return 0;
}

/*******
  END OF FILE
 *******/
