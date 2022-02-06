CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++11
TARGET  = std_puts
SRC     = std_puts.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
