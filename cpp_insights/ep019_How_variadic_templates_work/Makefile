CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = variadic_template
SRC     = variadic_template.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
