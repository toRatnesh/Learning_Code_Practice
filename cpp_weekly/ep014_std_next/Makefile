CC      = g++ -Wall -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++14 
TARGET  = Next
SRC     = Next.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

