CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = using_enum
SRC     = using_enum.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
