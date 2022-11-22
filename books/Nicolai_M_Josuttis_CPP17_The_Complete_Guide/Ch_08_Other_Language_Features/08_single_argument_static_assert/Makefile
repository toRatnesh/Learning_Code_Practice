CC      = g++ -Wall  -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17

ALL: 
	$(CC) -o single_argument_static_assert single_argument_static_assert.cpp

.PHONY: clean
clean:
	rm single_argument_static_assert
