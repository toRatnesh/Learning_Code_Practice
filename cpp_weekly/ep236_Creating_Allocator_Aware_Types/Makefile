CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++20
TARGET  = allocator_aware_types
SRC     = allocator_aware_types.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

