CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = jthread_and_stop_token
SRC     = jthread_and_stop_token.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
