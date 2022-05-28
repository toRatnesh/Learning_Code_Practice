CC      = g++ -Wall -Wpedantic -Wconversion  -g -std=c++20
TARGET  = pmr_Standard_Allocators
SRC     = pmr_Standard_Allocators.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
