CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -Wshadow -g -std=c++98
TARGET  = variable_shadowing
SRC     = variable_shadowing.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
