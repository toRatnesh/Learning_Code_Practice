CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g -std=c++20
TARGET  = format_and_fmt
SRC     = format_and_fmt.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
