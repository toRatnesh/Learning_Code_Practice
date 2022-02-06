CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = looping_and_algorithms
SRC     = looping_and_algorithms.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
