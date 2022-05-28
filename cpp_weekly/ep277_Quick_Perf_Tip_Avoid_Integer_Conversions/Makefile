CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11
TARGET  = avoid_integer_conversion
SRC     = avoid_integer_conversion.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
