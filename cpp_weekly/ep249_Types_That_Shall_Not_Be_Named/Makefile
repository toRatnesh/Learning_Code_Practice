CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++20
TARGET  = type_not_be_named
SRC     = type_not_be_named.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
