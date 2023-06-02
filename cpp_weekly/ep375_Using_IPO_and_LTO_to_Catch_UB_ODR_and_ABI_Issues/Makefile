CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g -std=c++11
TARGET  = ipo_lto_ub_odr_issue
SRC     = *.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -flto  -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
