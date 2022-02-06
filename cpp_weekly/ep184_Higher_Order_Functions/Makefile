CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = higher_order_functions
SRC     = higher_order_functions.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
