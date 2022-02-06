CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++20
TARGET  = cpp20_lambda_capture
SRC     = cpp20_lambda_capture.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
