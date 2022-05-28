/*********
  This example demonstrates about 'inline namespace' feature

  For more info visit:
https://www.youtube.com/watch?v=rUESOjhvLw0&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=321
https://www.ibm.com/docs/en/zos/2.2.0?topic=only-inline-namespace-definitions-c11
https://en.cppreference.com/w/cpp/language/namespace
 ************/

namespace myns {
	inline namespace v1_0_0 {
		struct S {
			char c1;
			int v1;
			char c2;
		};
		int fun(const S& s) { return s.v1 * (s.c1 + s.c2); }
	}  // namespace v1_0_0

	inline namespace v2_0_0 {
		struct S {
			int v1;
			char c1;
			char c2;
		};

		int fun(const S& s) { return s.v1 * (s.c1 + s.c2); }
	}  // namespace v2_0_0

}  // namespace myns

int main() {
	const myns::v2_0_0::S s{'A', 10, 'p'};
	return myns::fun(s);
}

/******
  END OF FILE
 ****/
