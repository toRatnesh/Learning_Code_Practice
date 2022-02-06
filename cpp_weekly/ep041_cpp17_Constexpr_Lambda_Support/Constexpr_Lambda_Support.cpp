/**************
 *
 * 	This example demonstrates the use of C++ 17 constexpr lambda support.
 *
 * **************/


int main() {
	constexpr const auto l_square = [](const auto val){ return val*val; };
	l_square(32);

	const int v1 = 32;
	l_square(v1);

	constexpr const int v2 = 13;
	l_square(v2);

	int v3 = 50;
	l_square(v3);

	double v4 = 3.4;
	l_square(v4);

	return 0;
}

/*******
 *	END OF FILE
 * *****/
