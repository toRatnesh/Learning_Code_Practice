CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++20
TARGET  = parameter_pack_in_lambda_capture
SRC     = parameter_pack_in_lambda_capture.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
