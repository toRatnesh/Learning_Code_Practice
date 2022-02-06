CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = avoid_const_cast
SRC     = avoid_const_cast.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
