CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++23
TARGET  = if_consteval
SRC     = if_consteval.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
