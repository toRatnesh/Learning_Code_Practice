CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++20
TARGET  = cpp20_lambda_comparator
SRC     = cpp20_lambda_comparator.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
