CC      = g++ -Wall -Wpedantic -Wconversion -fsanitize=address  -g -std=c++14
TARGET  = MapMemberAccess
SRC     = *.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

