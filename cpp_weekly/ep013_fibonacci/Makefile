CC      = g++ -Wall -Wpedantic -Wextra -g -std=c++11
TARGET  = fibonacci
SRC     = fibonacci.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
