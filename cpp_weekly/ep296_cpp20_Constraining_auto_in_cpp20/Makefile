CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = constraining_auto
SRC     = constraining_auto.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
