CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++17
TARGET  = lambda_comparator
SRC     = lambda_comparator.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
