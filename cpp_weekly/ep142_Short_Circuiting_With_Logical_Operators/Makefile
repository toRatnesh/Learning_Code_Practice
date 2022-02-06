CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++98
TARGET  = short_circuit
SRC     = short_circuit.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
