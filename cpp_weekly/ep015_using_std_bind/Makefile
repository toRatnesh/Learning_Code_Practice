CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++17
TARGET  = Bind
SRC     = Bind.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
