CC      = g++ -Wall -Wextra  -Wpedantic   -Wconversion -g -std=c++11
TARGET  = template_instantiation
SRC     = template_instantiation.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
