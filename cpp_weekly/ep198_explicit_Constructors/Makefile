CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = explicit_Constructors
SRC     = explicit_Constructors.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
