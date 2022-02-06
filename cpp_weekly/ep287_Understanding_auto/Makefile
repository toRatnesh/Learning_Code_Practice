CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = using_auto
SRC     = using_auto.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
