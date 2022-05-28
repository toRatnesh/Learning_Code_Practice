CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11
TARGET  = virtual_inheritance
SRC     = virtual_inheritance.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
