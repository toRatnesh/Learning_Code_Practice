CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++14
TARGET  = stop_using_namespace
SRC     = stop_using_namespace.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
