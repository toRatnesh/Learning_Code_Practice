CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++11
TARGET  = precision_loss_with_accumulate
SRC     = precision_loss_with_accumulate.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
