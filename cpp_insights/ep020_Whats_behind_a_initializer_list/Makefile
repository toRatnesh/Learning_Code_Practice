CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion  -g -std=c++11
TARGET  = initializer_list
SRC     = initializer_list.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
