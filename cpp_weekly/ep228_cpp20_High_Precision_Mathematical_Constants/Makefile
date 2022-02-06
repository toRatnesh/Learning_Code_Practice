CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = mathematical_Constants
SRC     = mathematical_Constants.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
