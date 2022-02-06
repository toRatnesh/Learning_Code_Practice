
/************************

  This example demonstrates the use of PMR.
  For more info visit:
https://en.cppreference.com/w/cpp/memory

Tutorial:   https://www.youtube.com/watch?v=q6A7cKFXjY0&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=223

NOTE:   Watch other episodes on PMR also


 ************************/


#include <vector>
#include <memory_resource>

void simple_vec() {   
	std::vector<int> lv{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
}

void pmr_vec_nobuf() {
	std::pmr::monotonic_buffer_resource mbr;
	std::pmr::polymorphic_allocator<int> pa{&mbr};
	std::pmr::vector<int> lv{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, pa};
}

void pmr_vec_buf() {
	std::array<std::byte, 20> buffer;
	std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
	std::pmr::polymorphic_allocator<int> pa{&mbr};
	std::pmr::vector<int> lv{{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, pa};
}


int main(int, char*[]) {
	simple_vec();
	pmr_vec_nobuf();
	pmr_vec_buf();
	return 0;   
}


/*****
  END OF FILE
 *****/
