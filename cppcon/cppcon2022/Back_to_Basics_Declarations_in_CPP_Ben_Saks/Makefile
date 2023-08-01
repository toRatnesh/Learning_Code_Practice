CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address -g -std=c++17
TARGET  = declarations_in_cpp 
SRC     = main.cpp declaration.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
