CC      = g++ -Wall -Wpedantic -g -std=c++11
TARGET  = lambda_to_functionPointer_cast
SRC     = lambda_to_functionPointer_cast.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
