CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = inline_variable
SRC     = inline_variable.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
