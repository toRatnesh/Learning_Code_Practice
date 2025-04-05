
CC     = g++ -Wall -Wextra -Wpedantic -Wconversion -g -std=c++14
TARGET = Item32_Use_init_capture_to_move_objects_into_closures
SRC	   = Item32_Use_init_capture_to_move_objects_into_closures.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
