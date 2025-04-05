
CC     = g++ -Wall -Wextra -Wpedantic -Wconversion -g -std=c++14
TARGET = Item31_Avoid_default_capture_modes
SRC	   = Item31_Avoid_default_capture_modes.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
