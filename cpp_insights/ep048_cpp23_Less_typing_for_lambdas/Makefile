CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++20
TARGET  = cpp23_simplified_lambda
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


