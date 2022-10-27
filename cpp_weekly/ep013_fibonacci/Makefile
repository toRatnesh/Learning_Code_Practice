CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -Wextra -g -std=c++11
TARGET  = fibonacci
SRC     = fibonacci.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
