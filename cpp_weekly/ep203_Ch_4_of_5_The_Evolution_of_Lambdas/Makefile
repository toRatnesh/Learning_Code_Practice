
CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17 
TARGET  = evolution_of_lambda
SRC     = evolution_of_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
