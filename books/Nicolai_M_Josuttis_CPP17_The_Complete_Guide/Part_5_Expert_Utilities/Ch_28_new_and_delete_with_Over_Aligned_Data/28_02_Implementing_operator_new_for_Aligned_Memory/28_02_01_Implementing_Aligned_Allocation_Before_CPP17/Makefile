CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -g -std=c++11
TARGET  = implementing_aligned_allocation_before_CPP17
SRC     = $(TARGET).cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) 

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
