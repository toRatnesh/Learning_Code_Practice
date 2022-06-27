/*************
  This example demonstrates about c++23 multidimensional subscript operator support
  For more info visit:
https://en.cppreference.com/w/cpp/23
https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2128r6.pdf
 ************/

#include <array>
#include <cstdio>

template<typename T, std::size_t width, std::size_t height>
struct Matrix {
	std::array<T, width*height> data;
	const auto & operator[](std::size_t X, std::size_t Y) const {
		return data[Y*width + X];
	}
};

int main() {
	const Matrix<int, 3, 4> mat{1,2,3,4,5,6,7,8,9,10,11,12};
	return mat[1,2];
}

/*************
  END OF FILE
 ************/
