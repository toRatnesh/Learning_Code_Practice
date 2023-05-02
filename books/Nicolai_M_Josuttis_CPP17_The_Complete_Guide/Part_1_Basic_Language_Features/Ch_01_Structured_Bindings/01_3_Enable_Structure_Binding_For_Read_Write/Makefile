CC	= g++ -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17
TARGET1 = Enable_Read-Only_Structured_Bindings
SRC1	= Enable_Read-Only_Structured_Bindings.cpp

TARGET2 = Enable_Structured_Bindings_with_Write_Access
SRC2	= Enable_Structured_Bindings_with_Write_Access.cpp

ALL : $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	$(CC) -o $(TARGET1) $(SRC1)

$(TARGET2): $(SRC2)
	$(CC) -o $(TARGET2) $(SRC2)

.PHONY: clean
clean:
	rm $(TARGET1) $(TARGET2)


