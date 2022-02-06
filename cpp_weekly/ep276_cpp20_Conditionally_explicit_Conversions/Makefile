CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = explicit_to_avoid_costly_copy
SRC     = explicit_to_avoid_costly_copy.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
