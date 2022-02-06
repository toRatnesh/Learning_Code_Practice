CC      = g++ -Wall -Wextra  -Wpedantic -g -std=c++11
TARGET  = StopUsingEndl
SRC     = StopUsingEndl.cpp

TARGET2  = Stream_vs_FileWrite
SRC2     = Stream_vs_FileWrite.cpp

ALL : $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

$(TARGET2): $(SRC2)
	$(CC) -o $(TARGET2) $(SRC2)

.PHONY: clean
clean:
	rm -f $(TARGET) $(TARGET2)

.PHONY: run
run:
	./$(TARGET)
	./$(TARGET2)

	
