ALL:
	g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address -g -std=c++20 -o smart_pointers_deleter smart_pointers_deleter.cpp
	g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address -g -std=c++17 -o smart_pointers_shared_ptr smart_pointers_shared_ptr.cpp
	g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address -g -std=c++17 -o smart_pointers_unique_ptr smart_pointers_unique_ptr.cpp
	g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address -g -std=c++17 -o smart_pointers_weak_ptr smart_pointers_weak_ptr.cpp


clean:
	rm smart_pointers_deleter smart_pointers_shared_ptr smart_pointers_unique_ptr smart_pointers_weak_ptr



