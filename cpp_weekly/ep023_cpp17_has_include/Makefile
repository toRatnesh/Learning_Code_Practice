CC      = g++ -Wall  -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = HasInclude
SRC     = HasInclude.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
