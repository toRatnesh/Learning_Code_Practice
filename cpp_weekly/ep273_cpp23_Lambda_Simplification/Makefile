CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++23
TARGET  = lambda_with_optional_paramlist
SRC     = lambda_with_optional_paramlist.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
