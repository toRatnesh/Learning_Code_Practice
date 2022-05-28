CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++14
TARGET  = feature_test_macros
SRC     = feature_test_macros.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
