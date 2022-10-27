CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++11
TARGET  = lambda_to_functionPointer_cast
SRC     = lambda_to_functionPointer_cast.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
