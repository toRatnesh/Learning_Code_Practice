CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++23
TARGET  = chunk_view_and_stride_view
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
