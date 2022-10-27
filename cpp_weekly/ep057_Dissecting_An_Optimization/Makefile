CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -Wextra -g -std=c++17
TARGET  = optimization
SRC     = optimization.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
