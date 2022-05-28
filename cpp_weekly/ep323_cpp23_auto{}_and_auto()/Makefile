CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++23
TARGET  = cpp23_auto_cast
SRC     = cpp23_auto_cast.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
