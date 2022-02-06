CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = what_is_lambda
SRC     = what_is_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
