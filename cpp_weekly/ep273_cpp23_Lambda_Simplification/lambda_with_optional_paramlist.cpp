/****************
 *	
 *	This example demonstrates the use of c++23 lambda which make () more optional for lambdas.
 *
 *	For more info visit:
 *	Tutorial video:	https://www.youtube.com/watch?v=fPWWo0MVK34&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=274
 *	https://en.cppreference.com/w/cpp/language/lambda
 *
 * ****************/


int main () {
    //auto l_lambda = [i=5]() mutable { return ++i;};	// since c++20
    auto l_lambda = [i=5] mutable { return ++i;};	// since c++23
    l_lambda();

    return 0;
}

/******
 *	END OF FILE
 * *******/
