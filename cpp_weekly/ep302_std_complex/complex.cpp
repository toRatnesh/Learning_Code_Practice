/***********************
  This example demonstrates about std::complex

  For more info visit:
https://en.cppreference.com/w/cpp/numeric/complex

 **********************/

#include <iostream>
#include <complex>

int main() {
	constexpr std::complex<double> lc(3.0, 4.0);

	std::clog << "real part " << '=' << lc.real() << '\n';
	std::clog << "imag part " << '=' << lc.imag() << '\n';

	std::clog << lc << '+' << 1 << '=' << (lc+1.0) << '\n';
	std::clog << 1 << '+' << lc << '=' << (1.0+lc) << '\n';

	std::clog << "tan" << lc << '=' << tan(lc) << '\n';

	return 0;
}


/*********
  END OF FILE
 **********/

