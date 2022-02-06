CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++14
TARGET  = benefit_of_noexcept
SRC     = benefit_of_noexcept.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
