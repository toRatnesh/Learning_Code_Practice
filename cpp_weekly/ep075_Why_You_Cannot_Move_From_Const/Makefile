CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17
TARGET  = cannot_move_const
SRC     = cannot_move_const.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
