CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++14
TARGET  = transparent_comparators
SRC     = transparent_comparators.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
