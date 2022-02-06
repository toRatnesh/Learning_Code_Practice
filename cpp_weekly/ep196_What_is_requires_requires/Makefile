CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = requires_requires
SRC     = requires_requires.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
