/****************
  This example demonstrates about most vexing parse.
  -> Most vexing parse occurs when we try to create an object by calling default contructor using paranthesis.
  -> For more detail check 
  1.  Item 7: Distinguish between () and {} when creating objects
Book: Effective Modern C++

2.  https://en.wikipedia.org/wiki/Most_vexing_parse

 **************/

struct test {
	int data = 42;
};

int main() {
	//test tobj();  // warning: empty parentheses were disambiguated as a function declaration [-Wvexing-parse]
	//return tobj.data;   // error: request for member 'data' in 'tobj', which is of non-class type 'test()'

	//test tobj2;
	test tobj2{};
	return tobj2.data;
}


/********
  END OF FILE
 ********/
