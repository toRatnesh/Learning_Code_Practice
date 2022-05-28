CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17
TARGET  = UseofInheritanceFromLambda
SRC     = UseofInheritanceFromLambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
