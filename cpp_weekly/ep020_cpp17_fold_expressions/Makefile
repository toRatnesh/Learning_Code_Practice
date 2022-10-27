CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = FoldExpressions
SRC     = FoldExpressions.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
