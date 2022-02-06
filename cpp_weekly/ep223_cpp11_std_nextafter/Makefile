CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = std_nextafter
SRC     = std_nextafter.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
