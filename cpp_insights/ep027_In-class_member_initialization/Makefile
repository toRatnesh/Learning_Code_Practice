CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++11
TARGET  = in-class_member_initialization
SRC     = in-class_member_initialization.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
