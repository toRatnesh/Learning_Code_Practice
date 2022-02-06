CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = garbageIn_garbageOut
SRC     = garbageIn_garbageOut.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
