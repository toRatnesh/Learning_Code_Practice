CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = generic_fun_vs_generic_lambda
SRC     = generic_fun_vs_generic_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
