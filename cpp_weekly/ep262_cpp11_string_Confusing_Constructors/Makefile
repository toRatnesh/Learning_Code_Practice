CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = string_confusing_constructors
SRC     = string_confusing_constructors.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
