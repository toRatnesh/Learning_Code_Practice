CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = negative_cost_struct
SRC     = negative_cost_struct.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
