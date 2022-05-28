
CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17 -DOPT_1
TARGET  = utilizing_lambda
SRC     = utilizing_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
