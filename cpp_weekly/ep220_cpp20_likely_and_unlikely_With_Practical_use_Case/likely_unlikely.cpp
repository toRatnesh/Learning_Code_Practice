/***************
  This example demonstrates the use of C++20 [[likely]] and [[unlikely]] attribute.

  For more info visit:
https://en.cppreference.com/w/cpp/language/attributes/likely

 ****************/


#include <vector>

#ifdef USE_LIKELY
#define LIKELY [[likely]]
#define UNLIKELY [[unlikely]]
#else
#define LIKELY
#define UNLIKELY
#endif

struct S {
	int id;
	int data;
};

auto & getValue(auto & vec, const auto id) {
	const auto pos = std::find_if(vec.begin(), vec.end(), [&id](const auto & elem){ return elem.id == id;});
	if(pos == vec.cend()) UNLIKELY {
		vec.push_back(S{id, 0});
		return vec.back();
	}
	else LIKELY {
		return *pos;
	}

}

int main(int, char*[]) {
	std::vector<S> lv{{0,10}, {1,11}, {2,12}, {3,13}};
	return getValue(lv, 7).id;    
}

/*****
  END OF FILE
 ******/


