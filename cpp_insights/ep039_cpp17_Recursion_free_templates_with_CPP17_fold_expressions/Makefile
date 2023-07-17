CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = recursion_free_templates_with_CPP17_fold_expressions
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
