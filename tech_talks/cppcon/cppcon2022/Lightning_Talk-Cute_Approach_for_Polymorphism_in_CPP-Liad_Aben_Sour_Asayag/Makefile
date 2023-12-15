CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++20 -DVIRTUAL_ON_AGGREGATE
TARGET  = polymorphism_approach
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
