CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++17
TARGET  = if_and_switch_with_initialization
SRC     = if_and_switch_with_initialization.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
