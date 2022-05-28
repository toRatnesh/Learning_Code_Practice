CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17 -fsanitize=address
TARGET  = stop_using_constexpr
SRC     = stop_using_constexpr.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
