CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11 -O3
TARGET  = attributes
SRC     = attributes.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
