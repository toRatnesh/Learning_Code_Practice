CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++23
TARGET  = signed_unsigned_size_t_Literals
SRC     = signed_unsigned_size_t_Literals.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
