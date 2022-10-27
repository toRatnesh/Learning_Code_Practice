CC      = gcc -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g
TARGET  = c_overload
SRC     = c_overload.c

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
