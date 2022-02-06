CC      = g++ -Wall -Wpedantic -g -std=c++20
TARGET  = type_not_be_named
SRC     = type_not_be_named.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
