
CC     = g++ -Wall -Wextra -Wpedantic -Wconversion -g -std=c++14
TARGET = Item34_Prefer_lambdas_to_std_bind
SRC	   = Item34_Prefer_lambdas_to_std_bind.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run:
	./$(TARGET)
