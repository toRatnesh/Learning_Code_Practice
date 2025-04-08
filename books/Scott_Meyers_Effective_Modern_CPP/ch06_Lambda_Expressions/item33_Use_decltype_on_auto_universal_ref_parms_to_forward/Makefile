
CC     = g++ -Wall -Wextra -Wpedantic -Wconversion -g -std=c++14
TARGET = Item33_Use_decltype_on_auto_universal_reference_parameters_to_std_forward_them
SRC	   = Item33_Use_decltype_on_auto_universal_reference_parameters_to_std_forward_them.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
