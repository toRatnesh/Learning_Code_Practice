CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++20
TARGET  = starts_with_and_ends_with
SRC     = starts_with_and_ends_with.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
