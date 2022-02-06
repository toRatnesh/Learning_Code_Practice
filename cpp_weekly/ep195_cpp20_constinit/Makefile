CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = constinit
SRC     = constinit.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
