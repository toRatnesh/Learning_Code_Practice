CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g -std=c++23
TARGET  = bind_back
SRC     = bind_back.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
