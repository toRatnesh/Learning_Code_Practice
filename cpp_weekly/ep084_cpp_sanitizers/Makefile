CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address -fsanitize=leak -g -std=c++11
TARGET  = sanitizers
SRC     = sanitizers.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
