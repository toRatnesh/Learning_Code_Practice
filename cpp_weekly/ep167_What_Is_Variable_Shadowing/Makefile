CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -Wshadow -g -std=c++98
TARGET  = variable_shadowing
SRC     = variable_shadowing.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
