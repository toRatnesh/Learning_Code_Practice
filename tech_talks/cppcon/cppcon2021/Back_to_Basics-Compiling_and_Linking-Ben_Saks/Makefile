CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17
TARGET  = template_instantiation
SRC     = main.cpp fun.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
