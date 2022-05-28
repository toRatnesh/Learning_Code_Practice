CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11 
TARGET  = valgrind_example
SRC     = valgrind_example.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	valgrind --tool=memcheck --leak-check=yes ./$(TARGET)
