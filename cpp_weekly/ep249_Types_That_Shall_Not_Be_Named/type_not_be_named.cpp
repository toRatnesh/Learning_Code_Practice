/**************
 *	This example demonstrates some types which shoud not be named.
 *	Lambda
 *	Local class
 *	Private inner class
 *
 *	For more info visit:
 *	https://www.youtube.com/watch?v=jWgSkM8N0Bc&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=252
 *
 *
 *
 * ************/

struct outer {
	private:
		struct inner {int i;};
	public:
		inner get_inner() { return inner{15}; }
};

auto privateInnerClass () 
{
	outer o;
	auto val = o.get_inner();
	return val;
}

// return type is auto because there is no way to know the return type in advance
auto localClassFunc() 
{
	struct MyStruct{};
	MyStruct s;
	return s;
}

// return type is auto because there is no way to know the type of lambda
auto fLambda ()     
{   
	return [](){};
}

int main() {
	auto l = [](){};
	using some_lambda_type = decltype(l);

	some_lambda_type l2;  // c++20 default constructible lambda      
	return 0;
}

/*********
 *	END OF FILE
 * *******/
