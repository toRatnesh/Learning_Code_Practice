CC      = g++ -Wall -Wpedantic -Wconversion  -Wextra -g -std=c++17
TARGET  = optimization
SRC     = optimization.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
