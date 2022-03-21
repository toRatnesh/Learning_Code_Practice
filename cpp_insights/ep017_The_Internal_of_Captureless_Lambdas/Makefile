CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++14
TARGET  = captureless_lambda
SRC     = captureless_lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
