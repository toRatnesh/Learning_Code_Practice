CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++17
TARGET  = string_view
SRC     = string_view.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
