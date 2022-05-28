CC      = g++ -Wall -Wpedantic -Wconversion  -g -std=c++20
TARGET  = Concept_and_constexpr-if
SRC     = Concept_and_constexpr-if.cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: run
run:
	./$(TARGET)
