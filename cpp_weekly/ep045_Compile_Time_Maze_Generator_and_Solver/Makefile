CC      = g++ -Wall -Wextra -Wpedantic -g -std=c++17 
TARGET  = Compile_Time_Maze_Generator
SRC     = Compile_Time_Maze_Generator.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
