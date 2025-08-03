
ifndef SRC
$(error Usage: make SRC=<src_filename> STD=<version>)
else ifndef STD
$(error Usage: make SRC=<src_filename> STD=<version>)
endif

CC      = g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=undefined,address,leak -fno-omit-frame-pointer -fsanitize-address-use-after-scope

ifeq ($(STD), 11)
	CC += -std=c++11
else ifeq ($(STD), 14)
	CC += -std=c++14
else ifeq ($(STD), 17)
	CC += -std=c++17
else ifeq ($(STD), 20)
	CC += -std=c++20
else
	CC += -std=c++17
endif


TARGET  = $(basename $(SRC))
SRC     = $(TARGET).cpp

ALL : $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
