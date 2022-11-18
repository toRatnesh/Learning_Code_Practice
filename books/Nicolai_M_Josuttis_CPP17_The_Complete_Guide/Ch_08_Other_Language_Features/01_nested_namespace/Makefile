CC      = g++ -Wall  -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17

ALL: 
	$(CC) -o nested_namespace nested_namespace.cpp

.PHONY: clean
clean:
	rm nested_namespace
