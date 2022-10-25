CC      = g++ -Wall  -Wextra  -Wpedantic -Wconversion -fsanitize=address  -g -std=c++17

ALL: 
	$(CC) -o 1_constexpr_Lambdas 1_constexpr_Lambdas.cpp
	$(CC) -o 2_Passing_Copies_of_this_to_Lambdas 2_Passing_Copies_of_this_to_Lambdas.cpp -lpthread
	$(CC) -o 3_Capturing_by_Reference 3_Capturing_by_Reference.cpp

.PHONY: clean
clean:
	rm 1_constexpr_Lambdas 2_Passing_Copies_of_this_to_Lambdas 3_Capturing_by_Reference
