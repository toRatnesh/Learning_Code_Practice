CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++20
TARGET  = traps_of_returning_references
SRC     = $(TARGET).cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
