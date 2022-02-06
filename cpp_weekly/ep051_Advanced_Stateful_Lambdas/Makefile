CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = Advanced_Stateful_Lambdas
SRC     = Advanced_Stateful_Lambdas.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
