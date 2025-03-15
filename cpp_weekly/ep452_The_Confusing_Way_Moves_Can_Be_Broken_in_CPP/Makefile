CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address,leak -fno-omit-frame-pointer -fsanitize-address-use-after-scope -std=c++23
TARGET  = way_Moves_Can_Be_Broken
SRC     = $(TARGET).cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
