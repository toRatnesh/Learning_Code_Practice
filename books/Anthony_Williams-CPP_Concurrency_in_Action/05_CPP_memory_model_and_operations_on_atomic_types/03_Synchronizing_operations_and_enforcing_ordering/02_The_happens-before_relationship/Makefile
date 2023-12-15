CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++17 -lpthread
TARGET  = happens-before_relationship
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
