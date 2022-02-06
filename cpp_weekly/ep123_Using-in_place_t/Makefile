CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = in_place_t
SRC     = in_place_t.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
