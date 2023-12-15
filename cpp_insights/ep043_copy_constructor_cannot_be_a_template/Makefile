CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address,undefined  -g -std=c++11
TARGET  = no_template_copy_cons
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


