CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11
TARGET  = const_and_non-const_diff
SRC     = const_and_non-const_diff.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
