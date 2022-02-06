CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++17
TARGET  = noexcept
SRC     = noexcept.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
