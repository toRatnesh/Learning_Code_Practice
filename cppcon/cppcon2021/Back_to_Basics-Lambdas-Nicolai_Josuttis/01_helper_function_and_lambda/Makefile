CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = helper_fun_and_lambda
SRC     = helper_fun_and_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
