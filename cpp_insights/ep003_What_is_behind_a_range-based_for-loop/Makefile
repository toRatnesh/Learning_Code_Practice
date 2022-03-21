CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++20
TARGET  = range_based_for_loop
SRC     = range_based_for_loop.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
