CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++20
TARGET  = bit_pattern_match
SRC     = bit_pattern_match.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
