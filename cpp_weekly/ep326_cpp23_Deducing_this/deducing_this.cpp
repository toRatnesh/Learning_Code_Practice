/***************************
  This exaple demonstrates about C++23 deducing this feature
  For more info visit:
https://en.cppreference.com/w/cpp/language/member_functions#Explicit_object_parameter

To be continued in future episodes ...

 **********************************/

#include <array>
#include <cstdio>

template<typename T, size_t width, size_t height>
struct Matrix {

	std::array<T, width*height> data;

	template<typename Self>
		auto & at(this Self && self, size_t X, size_t Y) {
			return std::forward<Self>(self).data.at((Y * width) + X);
		}

	/*  pre C++23
		T & at(size_t X, size_t Y) {
		return at(*this, X, Y);
		}
		const T & at(size_t X, size_t Y) const {
		return at(*this, X, Y);
		}

		private:
		template<typename myThis>
		static auto & at(myThis & obj, size_t X, size_t Y) {
		return obj.data.at((Y * width) + X);
		}
		*/
};

int main() {
	const Matrix<int, 2, 4> mat{1,2,3,4,5,6,7,8};
	//mat.at(2,3) = 7;
	return mat.at(2,3);
}

/****************
  END OF FILE
 ******************/
