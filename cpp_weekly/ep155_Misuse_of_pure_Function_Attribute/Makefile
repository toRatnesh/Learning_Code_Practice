CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11 -O3
TARGET  = misuse_of_pure
SRC     = misuse_of_pure.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
