CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++11
TARGET  = function-try-block
SRC     = function-try-block.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
