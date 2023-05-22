CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = print_attributes_of_a_passed_filesystem_path
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
