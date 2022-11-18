CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++11
TARGET  = lambda_issue
SRC     = lambda_issue.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
