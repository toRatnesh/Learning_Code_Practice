/********
  This example demonstrates about casting taking place implicitly by the compiler

 *******/

struct A { };
struct B { };
struct C {
	operator A() { 
		return {};
	}

	explicit operator B() { 
		return {};
	}
};

void dangerousFunction1(const A & a) { } 
void dangerousFunction2(const B & b) { } 
void fun(double d) { } 

int main() {
	fun(4);
	unsigned int lval = 5u;
	char lcarr[] = {2,4};
	dangerousFunction1(C{});

	//dangerousFunction2(C{}); // CE error: invalid initialization of reference of type ânst B&ârom expression of type C
	dangerousFunction2(static_cast<B>(C{}));

	return 0;
}

/****
  END OF FILE
 ****/
