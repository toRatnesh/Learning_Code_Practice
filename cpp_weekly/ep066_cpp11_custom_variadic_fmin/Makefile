CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++11
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
