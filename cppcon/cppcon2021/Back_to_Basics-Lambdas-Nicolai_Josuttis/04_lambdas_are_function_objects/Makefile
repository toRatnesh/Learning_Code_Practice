CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = lambdas_as_function_objects
SRC     = lambdas_as_function_objects.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
