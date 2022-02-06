CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++11
TARGET  = template_instantiation_and_virtual_functions
SRC     = template_instantiation_and_virtual_functions.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
