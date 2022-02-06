CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = disabling_move_from_const
SRC     = disabling_move_from_const.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
