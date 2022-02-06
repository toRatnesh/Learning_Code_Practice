CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = as_const
SRC     = as_const.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
