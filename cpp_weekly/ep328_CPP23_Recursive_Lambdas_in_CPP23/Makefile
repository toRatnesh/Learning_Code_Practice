CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++23
TARGET  = recursive_lambda
SRC     = recursive_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
