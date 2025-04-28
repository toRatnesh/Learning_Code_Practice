CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address,leak -fno-omit-frame-pointer -fsanitize-address-use-after-scope -std=c++14
TARGET  = alternatives_to_overloading_on_universal_references
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
