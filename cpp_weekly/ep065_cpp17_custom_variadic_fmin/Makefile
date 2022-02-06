CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++17
TARGET  = Fmin
SRC     = Fmin.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
