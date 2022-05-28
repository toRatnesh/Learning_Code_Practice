CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++20
TARGET  = lambda_in_cpp20
SRC     = lambda_in_cpp20.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
