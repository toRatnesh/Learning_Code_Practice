CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = lambda_captures
SRC     = lambda_captures.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
