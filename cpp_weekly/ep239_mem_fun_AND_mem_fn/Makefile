CC      = g++ -Wall -Wpedantic -Wconversion  -g -std=c++17
TARGET  = MemFunMemFn
SRC     = MemFunMemFn.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
