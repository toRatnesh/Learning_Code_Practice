/**************
 *	This example demonstrates how CPP is not only a object oriented language.
 *
 *	For more info visit:
 *	https://www.youtube.com/watch?v=AUT201AXeJg&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=138
 *	
 * **************/

struct S
{
	int data{};
	int get_data() {
		return data;
	}
};

int add (const int i, const int j)
{
	return i + j;
}

	template<typename T>
T add_template(const T t1, const T t2)
{
	return t1 + t2;
}

	template<typename T>
auto call(const T& func)
{
	return func(1,2);
}

int main()
{
	auto add_lambda = [](const int i, const int j){
		return i + j;
	};

	call(add);
	call(add_lambda);

	S s;
	s.get_data();

	return 0;
}

/*************
 *	END OF FILE
 * **********/
