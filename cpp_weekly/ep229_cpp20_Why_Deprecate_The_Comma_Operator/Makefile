CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = deprecate_The_Comma_Operator
SRC     = deprecate_The_Comma_Operator.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
