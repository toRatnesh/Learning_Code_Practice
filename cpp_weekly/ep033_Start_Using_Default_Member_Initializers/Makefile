CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17
TARGET  = Member_Initializers
SRC     = Member_Initializers.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
