CC      = g++ -Wall -Wextra -Wpedantic -Wconversion  -g -std=c++11
TARGET  = constexpr_vs_static_constexpr
SRC     = constexpr_vs_static_constexpr.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
