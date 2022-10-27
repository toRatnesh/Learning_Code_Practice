CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET  = pmr_not_best_option
SRC     = pmr_not_best_option.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

