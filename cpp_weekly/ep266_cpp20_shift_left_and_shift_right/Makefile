CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++20
TARGET  = shift_left_and_right
SRC     = shift_left_and_right.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
