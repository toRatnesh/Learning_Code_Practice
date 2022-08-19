/******************
  This example demonstrates about In-struct member initialization
  For more info visit:
https://en.cppreference.com/w/cpp/language/data_members#Member_initialization
https://www.youtube.com/watch?v=50meLVrBY8k
 ****************/

#include <iostream>

struct S1 {
	int a = 5;
	int b;
};

struct S2 {
	int a = 5;
	int b;
	S2(int m, int n) : a(m), b(n) { }
};

struct S3 {
	int a = 5;
	int b;
  	int c:4 = 6;	// valid since c++20
	S3() = default;
	S3(int n) : b(n) { }
};

int main() {
	S1 s1;
	std::clog << s1.a << ' ' << s1.b << '\n';
	S2 s2(7,9);
	std::clog << s2.a << ' ' << s2.b << '\n';
	S3 s31;
	std::clog << s31.a << ' ' << s31.b << '\n';
	S3 s32(3);
	std::clog << s32.a << ' ' << s32.b << '\n';
	return 0;
}

/****************
  END OF FILE
 *****************/

