CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -fsanitize=undefined,address,leak  -g -std=c++17 -lpthread
TARGET  = thread_safe_stack
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
