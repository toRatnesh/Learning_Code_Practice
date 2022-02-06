CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17 
TARGET  = constexpr_Compile_Time_Random
SRC     = constexpr_Compile_Time_Random.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
