CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++14
TARGET  = digitSeparator_binaryLiteral
SRC     = digitSeparator_binaryLiteral.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
