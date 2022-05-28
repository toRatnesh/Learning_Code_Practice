CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++17 -lpthread
TARGET  = StorageDurationWithLambda
SRC     = StorageDurationWithLambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
