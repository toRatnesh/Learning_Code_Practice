CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++17 -lpthread
TARGET  = ordering_non-atomic_operations_with_atomics
SRC     = $(TARGET).cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) 

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
