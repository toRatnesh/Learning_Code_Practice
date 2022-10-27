CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++20
TARGET  = pmr_mistakes
SRC     = pmr_mistakes.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
