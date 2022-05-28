CC      = g++ -Wall -Wpedantic -Wconversion  -g -std=c++11
TARGET  = Nodiscard
SRC     = Nodiscard.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
