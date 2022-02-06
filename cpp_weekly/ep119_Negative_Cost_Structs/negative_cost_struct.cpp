/******************
 *	In this tutorial Jason talks about difference in performance when 
 *	passing arguments using struct and passing all values without struct.
 *	This example demonstrates how using struct may result in a better performance on a compiler.
 *
 *	For more info visit tutorial video:
 *	https://www.youtube.com/watch?v=FwsO12x8nyM&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=121
 *
 * ******************/

#include <iostream>

struct St {
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	int a7;
	int a8;   
};

auto fun(
		int a1,
		int a2,
		int a3,
		int a4,
		int a5,
		int a6,
		int a7,
		int a8
	)
{
	return (a1+a2+a3+a4+a5+a6+a7+a8);
}

auto fun(struct St arg) {
	return (arg.a1+arg.a2+arg.a3+arg.a4+arg.a5+arg.a6+arg.a7+arg.a8);
}

auto call_by_arg() {
	return fun(11, 22, 33, 44, 55, 66, 77, 88);
}

auto call_by_struct(){
	return fun(St{11, 22, 33, 44, 55, 66, 77, 88});
}

int main() {
	call_by_arg();
	call_by_struct();

	return 0;
}

/*******
 *	END OF FILE
 * ********/
