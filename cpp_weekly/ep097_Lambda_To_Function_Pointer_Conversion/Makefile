CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++14
TARGET  = lambda_to_function_pointer
SRC     = lambda_to_function_pointer.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
