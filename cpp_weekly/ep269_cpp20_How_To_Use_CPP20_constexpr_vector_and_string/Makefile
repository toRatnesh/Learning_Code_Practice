CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = vector_and_string_in_constexpr_context
SRC     = vector_and_string_in_constexpr_context.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
