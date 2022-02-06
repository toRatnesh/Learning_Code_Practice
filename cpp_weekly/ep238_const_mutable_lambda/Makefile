CC      = g++ -Wall -Wpedantic -g -std=c++20
TARGET  = Mutable_Lambda
SRC     = Mutable_Lambda.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
