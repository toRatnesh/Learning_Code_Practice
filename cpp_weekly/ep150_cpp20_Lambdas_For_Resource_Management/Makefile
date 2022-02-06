CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = lambda_for_resource_mgmt
SRC     = lambda_for_resource_mgmt.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
