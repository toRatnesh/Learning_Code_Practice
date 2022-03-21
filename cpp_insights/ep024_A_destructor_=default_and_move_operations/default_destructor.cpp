/*************
  This example demonstrates about the effect of default destructor on move operations

  Making destructor default wihtout declaring move constructor prohibits move operations and instead uses copy
  So when destructor is default and move oprations is needed we need to declare move constructor also

  For more info visit:
https://www.youtube.com/watch?v=kc3GEznJFLs
 ***************/

#include <utility>

struct St {
	~St() = default;
	St(St && ) = default;
};

int main() {
	St s1{};
	St s2 = std::move(s1);
	return 0;
}

/*******
  END OF FILE
 *******/
