
ALL:
	g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address -o json_creator rapidjson_create.cpp
	g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address -o json_parser rapidjson_parser.cpp
	g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address -o json_streamwrapper rapidjson_streamwrapper.cpp

clean: 
	rm json_creator json_parser json_streamwrapper 
	
.PHONY: ALL
