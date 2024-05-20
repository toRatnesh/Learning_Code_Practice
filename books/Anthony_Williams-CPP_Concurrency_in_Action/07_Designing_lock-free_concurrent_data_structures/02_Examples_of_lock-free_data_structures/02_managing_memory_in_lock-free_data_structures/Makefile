#CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++20
CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -g -std=c++20
TARGET  = manage_memory_in_lock_free_DS
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


