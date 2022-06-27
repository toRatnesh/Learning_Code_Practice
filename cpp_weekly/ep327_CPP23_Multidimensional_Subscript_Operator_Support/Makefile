CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++23
TARGET  = deducing_this.cpp
SRC     = deducing_this.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
