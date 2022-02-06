CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11 
TARGET  = constexpr_and_noexcept
SRC     = constexpr_and_noexcept.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
