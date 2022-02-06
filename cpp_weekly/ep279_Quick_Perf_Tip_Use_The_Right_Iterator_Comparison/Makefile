CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = right_iterator_comparison
SRC     = right_iterator_comparison.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
