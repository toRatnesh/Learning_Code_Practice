CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = generic_lambda_and_lambda_without_capture
SRC     = generic_lambda_and_lambda_without_capture.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
